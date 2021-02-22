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

	boundingBox_ = Rectangle(x_, y_, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
	

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
	boundingBox_ = Rectangle(x_, y_,
		sourceRect_.w * globals::SPRITE_SCALE, sourceRect_.h * globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const {
//Rectangle Sprite::getBoundingBox(){
	return boundingBox_;
}

const sides::Side Sprite::getCollisionSide(Rectangle& other) const {
	// How much our rectangle is inside the other rectangle on each side
	int amtRight, amtLeft, amtTop, amtBottom;
	// Which is the lowest amount that it's in (overlapping) is the side of our colliding on
	amtRight = boundingBox_.getRight() - other.getLeft();
	amtLeft = other.getRight() - boundingBox_.getLeft();
	amtTop = other.getBottom() - boundingBox_.getTop();
	amtBottom = boundingBox_.getBottom() - other.getTop();

	int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtBottom), abs(amtTop) };
	//std::sort(vals, vals + 4, [](int a, int b) {return a < b; });
	//std::sort(vals, vals + 4, std::greater<int>());

	int lowest = vals[0];
	for (int i = 0; i < 4; i++) {
		if (vals[i] < lowest) {
			lowest = vals[i];
		}
	}

	return
		lowest == abs(amtRight) ? sides::RIGHT :
		lowest == abs(amtLeft) ? sides::LEFT :
		lowest == abs(amtBottom) ? sides::BOTTOM :
		lowest == abs(amtTop) ? sides::TOP :
		sides::NONE;
}

Sprite::~Sprite() {

}