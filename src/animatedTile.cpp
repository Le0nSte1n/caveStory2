#include "animatedTile.h"

AnimatedTile::AnimatedTile(std::vector<Vector2> tilesetPositions, int duration,
	SDL_Texture* tileset, Vector2 size, Vector2 position):
	Tile(tileset, size, tilesetPositions[0], position),
	tilesetPositions_(tilesetPositions),
	duration_(duration),
	tileToDraw_(0) {

}

void AnimatedTile::update(int elapsedTime) {
	// Timer code
	if (amountOfTime_ <= 0) {
		if (tileToDraw_ == tilesetPositions_.size() - 1)
			tileToDraw_ = 0;
		else
			tileToDraw_++;
		amountOfTime_ = duration_;
	}
	else {
		amountOfTime_ -= elapsedTime;
	}
	Tile::update(elapsedTime);
}

void AnimatedTile::draw(Graphics& graphics) {
	SDL_Rect  destRect = { position_.x, position_.y,
		size_.x * globals::SPRITE_SCALE, size_.y * globals::SPRITE_SCALE };
	SDL_Rect sourceRect = { tilesetPositions_[tileToDraw_].x, tilesetPositions_[tileToDraw_].y, 
		size_.x, size_.y };
	graphics.blitSurface(tileset_, &sourceRect, &destRect);
}