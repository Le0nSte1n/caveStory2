#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "globals.h"
#include "tile.h"
#include "tinyxml2.h"
#include "rectangle.h"

#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace tinyxml2;

struct Tileset;

class Level {
public:
	Level();

	/* Level
	 * mapNmae: the name of the map loaded
	 * spwanPoint: where to spawn the player
	 */
	Level(std::string mapName, Vector2 spwanPoint, Graphics& graphics);

	void draw(Graphics& graphics);
	void update(float elapsedTime);

	std::vector<Rectangle> checkTileCollisions(const Rectangle& other);

	const Vector2 getSpawnPoint() const;

	~Level();
private:
	std::string mapName_;
	Vector2 spawnPoint_;

	Vector2 size_;
	Vector2 tileSize_;

	SDL_Texture* backgroundTexture_;

	std::vector<Tile> tileList_;
	std::vector<Tileset> tilesets_;
	std::vector<Rectangle> collisionRects_;	// all tile collision rectangles will go into this vecotr

	/* void loadMap
	 * Loads a map
	 * parse XML files for map infos
	 */
	void loadMap(std::string mapName, Graphics& graphics);

};

// Tileset structure
struct Tileset{
	SDL_Texture* Texture;
	int FirstGid;	// the first number of the tileset

	Tileset() {
		FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid) {
		Texture = texture;
		FirstGid = firstGid;
	}
};

#endif // !LEVEL_H

