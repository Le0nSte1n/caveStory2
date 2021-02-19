#include "level.h"
#include "tinyxml2.h"

#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

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
			destRect.x = x * 64 * globals::SPRITE_SCALE;
			destRect.y = y * 64 * globals::SPRITE_SCALE;
			destRect.w = 64 * globals::SPRITE_SCALE;
			destRect.h = 64 * globals::SPRITE_SCALE;
			graphics.blitSurface(backgroundTexture_, &sourceRect, &destRect);
		}
	}
}

void Level::loadMap(std::string mapName, Graphics& graphics) {
	//// Temporarily load the background
	//backgroundTexture_ = SDL_CreateTextureFromSurface(graphics.getRenderer(),
	//	graphics.loadImage("content\\backgrounds\\bkBlue.png"));
	//size_ = Vector2(1280, 960);

	// Parse the .tmx file
	XMLDocument doc;	// represents the entire XML dcoument
	std::stringstream ss;
	ss << "content\\maps\\" << mapName << ".tmx";	// Pass in Map 1, we get content\\maps\\Map 1.tmx
	doc.LoadFile(ss.str().c_str());	// convert stringstream to string then to C string

	// Start parsing
	XMLElement* mapNode = doc.FirstChildElement("map");

	// Get the width and the height of the whole map and store it in size_
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	size_ = Vector2(width, height);

	// Get the width and the height of the tiles and store it in tileSize
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	tileSize_ = Vector2(tileWidth, tileHeight);

	// Load the tilesets 
	// 

}


Level::~Level(){

}