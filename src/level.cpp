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
	//// Draw the background
	//SDL_Rect sourceRect = { 0,0,64,64 };
	//SDL_Rect destRect;
	//// A loop wo draw the background since the bkBlue.png 
	//// is 64*64 which is smaller than the screen
	//for (int x = 0; x < size_.x / 64; x++) {
	//	for (int y = 0; y < size_.y / 64; y++) {
	//		destRect.x = x * 64 * globals::SPRITE_SCALE;
	//		destRect.y = y * 64 * globals::SPRITE_SCALE;
	//		destRect.w = 64 * globals::SPRITE_SCALE;
	//		destRect.h = 64 * globals::SPRITE_SCALE;
	//		graphics.blitSurface(backgroundTexture_, &sourceRect, &destRect);
	//	}
	//}

	for (int i = 0; i < tileList_.size(); i++) {
		tileList_[i].draw(graphics);
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
	ss << "content/maps/" << mapName << ".tmx";	// Pass in Map 1, we get content\\maps\\Map 1.tmx
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

	// Loading the tilesets 
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != nullptr) {
		while (pTileset) {
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;
			std::stringstream ss;
			ss << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(
				graphics.getRenderer(), graphics.loadImage(ss.str()));
			tilesets_.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset");	// jump to next "tileSet" node if there is one
		}
	}

	// Loading the layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != nullptr) {
		while (pLayer) {
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != nullptr) {
				while (pData) {
					// Loading the tile element
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != nullptr) {
						int tileCounter = 0;
						while (pTile) {
							// Build each individual tile here
							// If gid is 0, no tile should be drawn, continue loop
							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							// Get the tileset for this specific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < tilesets_.size(); i++) {
								if (tilesets_[i].FirstGid <= gid) {
									// This is the tileset we want
									tls = tilesets_[i];
									break;
								}
							}
							if (tls.FirstGid == -1) {
								// No tileset was found for this gid
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
									break;
							}
							// Get the position of the tile in the level
							int xx = 0, yy = 0;
							xx = (tileCounter % width);
							xx *= tileWidth;
							yy = (tileCounter / width) * tileHeight;
							Vector2 finalTilePosition = Vector2(xx, yy);

							// Calculate the position of the tile in the tileset
							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsxx = gid % (tilesetWidth / tileWidth) - 1;
							tsxx *= tileWidth;
							int tsyy = gid / (tilesetWidth / tileWidth);
							tsyy *= tileHeight;
							Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

							// Build the actual tile and add it to the level's tile list
							Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
								finalTilesetPosition, finalTilePosition);
							tileList_.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
				}
			 }

			pLayer = pLayer->NextSiblingElement("layer");	// the same trick to loop
		}
	}

}


Level::~Level(){

}