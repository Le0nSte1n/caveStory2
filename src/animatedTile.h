#pragma once
#ifndef ANIMATEDTILE_H
#define ANIMATEDTILE_H

#include "tile.h"
#include "globals.h"

#include <vector>

class AnimatedTile : public Tile {
public:
	AnimatedTile() {}

	AnimatedTile(std::vector<Vector2> tilesetPositions, int duration,
		SDL_Texture* tileset, Vector2 size, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics& graphics);

	~AnimatedTile() {}
protected:
	int amountOfTime_ = 0;
	bool notDone_ = false;
private:
	std::vector<Vector2> tilesetPositions_;	// Positions of each of the frames within the tile set
	int tileToDraw_;
	int duration_;
};

struct AnimatedTileInfo {
public:
	int TilesetsFirstGid;
	int StartTileID;
	std::vector<int> TileIds;
	int Duration;
};

#endif // !ANIMATEDTILE_H
