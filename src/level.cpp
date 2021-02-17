#include "level.h"

Level::Level(){

}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics& graphics):
	mapName_(mapName), spawnPoint_(spawnPoint), size_(Vector2(0, 0)) {
	loadMap(mapName, graphics);

}

void Level::update(float elapsedTime) {

}

void Level::draw(Graphics& graphics) {
	// Draw the background
	SDL_Rect sourceRect = { 0,0,64,64 };
	SDL_Rect destRect;
	// A loop wo draw the background since the bkBlue.png 
	// is 64*64 which is smaller than the screen
	for (int x = 0; x < size_.x / 64; x++) {
		for (int y = 0; y < size_.y / 64; y++) {
			destRect.x = x * 64;
			destRect.y = y * 64;
			destRect.w = 64;
			destRect.h = 64;
			graphics.blitSurface(backgroundTexture_, &sourceRect, &destRect);
		}
	}
}

void Level::loadMap(std::string mapName, Graphics& graphics) {
	// load the background
	backgroundTexture_ = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		graphics.loadImage("content\\backgrounds\\bkBlue.png"));
	size_ = Vector2(1280, 960);
}

Level::~Level(){

}