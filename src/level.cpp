#include "level.h"

Level::Level(){

}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics& graphics):
	mapName_(mapName), spawnPoint_(spawnPoint), size_(Vector2(0, 0)) {
	loadMap(mapName, graphics);

}

void Level::update(float elapsedTime) {
	for (int i = 0; i < animatedTileList_.size(); i++) {
		animatedTileList_[i].update(elapsedTime);
	}
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
	for (int i = 0; i < animatedTileList_.size(); i++) {
		animatedTileList_[i].draw(graphics);
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
			//char* path;
			std::stringstream ss;
			ss << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(
				graphics.getRenderer(), graphics.loadImage(ss.str()));
			tilesets_.push_back(Tileset(tex, firstgid));

			// Get all of the animations for the tilesets
			XMLElement* pTileA = pTileset->FirstChildElement("tile");
			if (pTileA != nullptr) {
				while (pTileA) {
					AnimatedTileInfo ati;	// animatedTIle info
					ati.StartTileID = pTileA->IntAttribute("id") + firstgid;	// !
					ati.TilesetsFirstGid = firstgid;
					XMLElement* pAnimation = pTileA->FirstChildElement("animation");
					if (pAnimation != nullptr) {
						while (pAnimation) {
							XMLElement* pFrame = pAnimation->FirstChildElement("frame");
							if (pFrame != nullptr) {
								while (pFrame) {
									ati.TileIds.push_back(pFrame->IntAttribute("tileid") + firstgid);
									ati.Duration = pFrame->IntAttribute("duration");
									pFrame = pFrame->NextSiblingElement("frame");
								}
							}
							pAnimation = pAnimation->NextSiblingElement("animation");
						}
					}
					animatedTileInfos_.push_back(ati);
					pTileA = pTileA->NextSiblingElement("tile");
				}
			}
			pTileset = pTileset->NextSiblingElement("tileset");	// jump to next "tileSet" node if there is one
		}
	}

	// Loading the layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != nullptr) {
		//printf("layer\n");
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
							// Keep loop
							// When the loop is done, the closet tileset is found
							int closet = 0;
							for (int i = 0; i < tilesets_.size(); i++) {
								if (tilesets_[i].FirstGid <= gid) {
									if (tilesets_[i].FirstGid > closet) {
										closet = tilesets_[i].FirstGid;
										tls = tilesets_[i];
									}
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

							//// Calculate the position of the tile in the tileset
							//int tilesetWidth, tilesetHeight;
							//SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							//int tsxx = gid % (tilesetWidth / tileWidth) - 1;
							//tsxx *= tileWidth;
							//int tsyy = (gid - tls.FirstGid) / (tilesetWidth / tileWidth);	// Needs to be (gid - tls.FirstGid) here
							//tsyy *= tileHeight;
							//Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
							Vector2 finalTilesetPosition = getTilesetPosition(tls, gid, tileWidth, tileHeight);

							// Build the actual tile and add it to the level's tile list
							bool isAnimatedTile = false;
							AnimatedTileInfo ati;
							for (int i = 0; i < animatedTileInfos_.size(); i++) {
								if (animatedTileInfos_[i].StartTileID == gid) {
									ati = animatedTileInfos_[i];
									isAnimatedTile = true;
									break;
								}
							}
							if (isAnimatedTile) {
								std::vector<Vector2> tilesetPositions;
								for (int i = 0; i < ati.TileIds.size(); i++) {
									tilesetPositions.push_back(getTilesetPosition(tls, ati.TileIds[i],
										tileWidth, tileHeight));
								}
								AnimatedTile tile(tilesetPositions, ati.Duration, 
									tls.Texture, Vector2(tileWidth, tileHeight), finalTilePosition);
								animatedTileList_.push_back(tile);
							}
							else {
								Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
									finalTilesetPosition, finalTilePosition);
								tileList_.push_back(tile);
							}
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

	// Parse out the collisions
	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != nullptr) {
		while (pObjectGroup) {
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ss;
			ss << name;
			if (ss.str() == "collisions") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != nullptr) {
					while (pObject) {
						float x, y, width, height;
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						collisionRects_.push_back(Rectangle(
							std::ceil(x) * globals::SPRITE_SCALE,
							std::ceil(y) * globals::SPRITE_SCALE,
							std::ceil(width) * globals::SPRITE_SCALE,
							std::ceil(height) * globals::SPRITE_SCALE
						));	// Using ceil functiont to convert the parameters from float to integer

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			// Other objectives go here with an else if (ss.str() == "whatever") 

			else if (ss.str() == "slopes") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != nullptr) {
					while (pObject) {
						std::vector<Vector2> points;
						Vector2 p1;
						p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), 
							std::ceil(pObject->FloatAttribute("y")));
						
						XMLElement* pPloyline = pObject->FirstChildElement("polyline");
						if (pPloyline != nullptr) {
							std::vector<std::string> pairs;
							const char* pointString = pPloyline->Attribute("points");
							std::stringstream ss;
							ss << pointString;
							Utils::split(ss.str(), pairs, ' ');

							// Now we have each of the pairs
							// Loop split them into Vector2s and then store them in the points vecotr
							for (int i = 0; i < pairs.size(); i++) {
								std::vector<std::string> ps;
								Utils::split(pairs[i], ps, ',');
								points.push_back(Vector2(std::stoi(ps[0]), std::stoi(ps[1])));
							}
						}

						for (int i = 0; i < points.size(); i += 2) {
							slopes_.push_back(Slope(
								Vector2((p1.x + points[i < 2 ? i : i - 1].x)* globals::SPRITE_SCALE,
									(p1.y + points[i < 2 ? i : i - 1].y)* globals::SPRITE_SCALE),
								Vector2((p1.x + points[i < 2 ? i + 1 : i].x)* globals::SPRITE_SCALE,
									(p1.y + points[i < 2 ? i + 1 : i].y)* globals::SPRITE_SCALE)
							));
						}
						/*for (int i = 0; i < points.size() - 1; i++) {
							Vector2 point1 = Vector2((p1.x + points.at(i).x) * globals::SPRITE_SCALE,
								(p1.y + points.at(i).y) * globals::SPRITE_SCALE);
							Vector2 point2 = Vector2((p1.x + points.at(i + 1).x) * globals::SPRITE_SCALE,
								(p1.y + points.at(i + 1).y) * globals::SPRITE_SCALE);
							Slope slope = Slope(point1, point2);

							slopes_.push_back(slope);
						}*/

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			else if (ss.str() == "spawn points") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				//printf("Hi\n");
				if (pObject != nullptr) {
					//printf("Hi\n");
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "player") {
							spawnPoint_ = Vector2(std::ceil(x) * globals::SPRITE_SCALE,
								std::ceil(y) * globals::SPRITE_SCALE);
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}

}

Vector2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight) {
	// Calculate the position of the tile in the tileset
	int tilesetWidth, tilesetHeight;
	SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
	int tsxx = gid % (tilesetWidth / tileWidth) - 1;
	tsxx *= tileWidth;
	int tsyy = (gid - tls.FirstGid) / (tilesetWidth / tileWidth);	// Needs to be (gid - tls.FirstGid) here
	tsyy *= tileHeight;
	Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
	return finalTilesetPosition;
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle& other) {
	std::vector<Rectangle> others;
	for (int i = 0; i < collisionRects_.size(); i++) {
		if (collisionRects_[i].collidesWith(other)) {
			others.push_back(collisionRects_[i]);
		}
	}
	return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle& other) {
	std::vector<Slope> others;
	for (int i = 0; i < slopes_.size(); i++) {
		if (slopes_[i].collidesWith(other)) {
			others.push_back(slopes_[i]);
		}
	}
	return others;
}

const Vector2 Level::getSpawnPoint() const {
	return spawnPoint_;
}

Level::~Level(){

}