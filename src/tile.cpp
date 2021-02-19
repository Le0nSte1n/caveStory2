#include "tile.h"

Tile::Tile(){

}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position):
	tileset_(tileset), 
	size_(size), 
	tilesetPosition_(tilesetPosition),
	position_(Vector2(position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE)){

}

void Tile::update(int elapsedTime) {

}

void Tile::draw(Graphics& graphics) {
	SDL_Rect destRect = { position_.x, position_.y,
		size_.x * globals::SPRITE_SCALE, size_.y * globals::SPRITE_SCALE };
	SDL_Rect sourceRect = { tilesetPosition_.x, tilesetPosition_.y,size_.x, size_.y };
	graphics.blitSurface(tileset_, &sourceRect, &destRect);
}

void Tile::draw() {

}

Tile::~Tile(){

}