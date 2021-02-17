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
	
	player_ = Player(graphics,100, 100);
	level_ = Level("map 1", Vector2(100, 100), graphics);

	int LAST_UPDATE_TIME_MS = SDL_GetTicks();
	// start the game loop
	while (true) {
		input.beginNewFrame();	//	reset pressed keys and released keys

		if (SDL_PollEvent(&event)) {
			//switch (event.type){
			//case SDL_KEYDOWN:
			//	if (event.key.repeat == 0)	// not holding down a key
			//		input.keyDownEvent(event);
			//	break;
			//case SDL_KEYUP:
			//	input.keyDownEvent(event);
			//	break;
			//case SDL_QUIT:
			//	return; 
			//	break;
			//default:
			//	break;
			//}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0)	// not holding down a key
					input.keyDownEvent(event);
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)	// quit out of the game loop
			return;
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true)
			player_.moveLeft();
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true)
			player_.moveRight();

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
}