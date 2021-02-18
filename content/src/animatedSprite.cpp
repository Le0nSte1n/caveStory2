#include "animatedSprite.h"

AnimatedSprite::AnimatedSprite() {

}
AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY,
	int width, int height, float posX, float posY, float timeToUpdate) :
	Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	frameIndex_(0),
	timeElapsed_(0.0),	/* don't forget to initialize 'timeElapsed' or the image will not move but freeze*/
	timeToUpdate_(timeToUpdate),
	visible_(true),
	currentAnimationOnce_(false),
	currentAnimation_("") {}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	// cut up the sprite sheet into the correct number of frames, and store the rectangles in the map
	bool flag1 = true, flag2 = false;
	std::vector<SDL_Rect> rectangles;

	//for (int i = 0; i < frames; i++) {
	//	if (x == 0 && i == 2 && flag1) {
	//		i = 0;
	//		flag1 = false;
	//		flag2 = true;
	//	}
	//	if(x == 0 && i == 1 && flag2) {
	//		i = 2;
	//	}
	//	printf("%d\n", i);
	//	SDL_Rect newRect = { x + i * width, y, width, height };	// a small rectangls is cut out each time
	//	rectangles.push_back(newRect);
	//}

	for (int i = 0; i < frames; i++) {
		//SDL_Rect newRect = { (i + x) * width, y, width, height };
		SDL_Rect newRect = { x + i * width, y, width, height };	// a small rectangls is cut out each time
		rectangles.push_back(newRect);
	}

	// insert the new animation to the map
	animations_.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	offsets_.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimation() {
	animations_.clear();
	offsets_.clear();
}

void AnimatedSprite::stopAnimation() {
	frameIndex_ = 0;
	animationDone(currentAnimation_);
}

void AnimatedSprite::setVisible(bool visible) {
	visible_ = visible;
}

// be caful not to redefine the default parmeter "once"
void AnimatedSprite::playAnimation(std::string animation, bool once) {
	currentAnimationOnce_ = once;
	if (currentAnimation_ != animation) {
		currentAnimation_ = animation;
		frameIndex_ = 0;
	}
}

void AnimatedSprite::update(float elapsedTime) {
	Sprite::update();

	timeElapsed_ += elapsedTime;
	if (timeElapsed_ > timeToUpdate_) {	// need to change frames
		timeElapsed_ -= timeToUpdate_;	// otherwise it will run rapidly

		// if not the last frame, just ++
		if (frameIndex_ < animations_[currentAnimation_].size() - 1) {
			frameIndex_++;
		}
		else {
			if (currentAnimationOnce_ == true)
				setVisible(false);
			frameIndex_ = 0;	// set frameIndex to the beginning
			animationDone(currentAnimation_);	// the current animation finished
		}
	}
}

void AnimatedSprite::draw(Graphics& graphics, int x, int y) {
	if (visible_) {
		SDL_Rect destinationRectabgle;
		destinationRectabgle.x = x + offsets_[currentAnimation_].x;	// why not x_ and y_?
		destinationRectabgle.y = y + offsets_[currentAnimation_].y;
		destinationRectabgle.w = sourceRect_.w * globals::SPRITE_SCALE;
		destinationRectabgle.h = sourceRect_.h * globals::SPRITE_SCALE;

		SDL_Rect sourceRect = animations_[currentAnimation_][frameIndex_];
		graphics.blitSurface(sprite_sheet_, &sourceRect, &destinationRectabgle);
	}
}

AnimatedSprite::~AnimatedSprite() {

}