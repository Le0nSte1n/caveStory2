#pragma once
#ifndef TILE_H
#define TILE_H

#include "graphics.h"
#include "globals.h"


class Tile{
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics& graphics);
	void draw();
	~Tile();


private:
	SDL_Texture* tileset_;	// each tile comes from a tileset
	Vector2 size_;	// the size of the tile
	Vector2 tilesetPosition_;	// the position on the tileset of the tile 
	Vector2 position_;	// the position on the map of the tile
};

#endif // !TILE_H
