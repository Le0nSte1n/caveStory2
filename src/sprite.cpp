#include "sprite.h"

Sprite::Sprite() {

}
Sprite::Sprite(Graphics& graphics, const std::string& filePath, int sourceX,
	int sourceY, int width, int height, float posX, float posY) :x_(posX), y_(posY) {
	sourceRect_.x = sourceX;
	sourceRect_.y = sourceY;
	sourceRect_.w = width;
	sourceRect_.h = height;

	sprite_sheet_ = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (sprite_sheet_ == nullptr)
		printf("\nError: Unable to load image\n");
}

void Sprite::draw(Graphics& graphics, int x, int y) {
	/* globals::SPRITE_SCALE
	 * Original image grabed from MyChar.png is too small to see it clearly,
	 * so it needs to be magnified to twice the size
	 */
	SDL_Rect destinationRectangle = { x,y,sourceRect_.w * globals::SPRITE_SCALE, sourceRect_.h * globals::SPRITE_SCALE };
	graphics.blitSurface(sprite_sheet_, &sourceRect_, &destinationRectangle);
}

void Sprite::update() {

}

Sprite::~Sprite() {

}