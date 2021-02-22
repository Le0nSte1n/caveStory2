#include "game.h"

namespace {
	const int FPS = 50;	// frames per second
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;	// max time a frame is allowed to last
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	level_ = Level("Map 1", Vector2(100, 100), graphics);
	std::cout << level_.getSpawnPoint().x << " " << level_.getSpawnPoint().y << std::endl;
	player_ = Player(graphics, level_.getSpawnPoint());

	int LAST_UPDATE_TIME_MS = SDL_GetTicks();
	// start the game loop
	while (true) {
		input.beginNewFrame();	//	reset pressed keys and released keys

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0)	// not holding down a key
					input.keyDownEvent(event);
			}
			else if (event.type == SDL_KEYUP)
				input.keyUpEvent(event);
			else if (event.type == SDL_QUIT)
				return;
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))	// quit out of the game loop
			return;
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
			player_.moveLeft();
			//printf("move left\n");
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			player_.moveRight();
			//printf("move right\n");
		}

		//if (input.wasKeyPressed(SDL_SCANCODE_Z))
		//	printf("Z wasKeyPressed\n");
		//if (input.isKeyHeld(SDL_SCANCODE_Z))
		//	printf("Z isKeyHeld\n");
		//if (input.wasKeyReleased(SDL_SCANCODE_Z))
		//	printf("Z wasKeyReleased\n");

		if (input.wasKeyPressed(SDL_SCANCODE_Z) && input.isKeyHeld(SDL_SCANCODE_Z)) {
			player_.jump();
			//printf("jump\n");
		}

		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT))
			player_.stopMoving();

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME_MS;
		/* Notes
		 * A time check is needed here to make sure (by doing some calculation)that    
		 * the main character can travel the same distance through the same time in
		 * different computers. That is to say, all movement not matter the computer's 
		 * speed is the same. Otherwise it will going to be weird. (very imprtant, can be 
		 * understood later)
		 */
		update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));	

		LAST_UPDATE_TIME_MS = CURRENT_TIME_MS;

		draw(graphics);
	}
}

void Game::draw(Graphics& graphics) {
	graphics.clear();

	// Draw the level before drawing the player
	level_.draw(graphics);
	player_.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	player_.update(elapsedTime);
	level_.update(elapsedTime);

	// Check collisions
	//int n = level_.checkTileCollisions(player_.getBoundingBox()).size();
	//printf("%d\n", n);
	//player_.getBoundingBox().print();
	std::vector<Rectangle> others;
	if ((others = level_.checkTileCollisions(player_.getBoundingBox())).size() > 0) {
		//Player collided with at least one tile. Handle it.
		player_.handleTileCollisions(others);
	}
	// Check slope collisions
	std::vector<Slope> otherSlopes;
	if ((otherSlopes = level_.checkSlopeCollisions(player_.getBoundingBox())).size() > 0) {
		player_.handleSlopeCollisions(otherSlopes);
	}
	
}