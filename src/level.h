#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "globals.h"

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

	~Level();
private:
	std::string mapName_;
	Vector2 spawnPoint_;

	Vector2 size_;
	Vector2 tileSize_;

	SDL_Texture* backgroundTexture_;

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

