#include "player.h"

namespace player_constants{
	const float WALK_SPEED = 0.2f;

	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player() {

}

Player::Player(Graphics& graphics, Vector2 spawnPoint):
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
	dx_(0),
	dy_(0),
	facing_(RIGHT),
	grounded_(false){
	// grounded_ will be set to true after falling to the graound
	//graphics.loadImage("content\\sprites\\MyChar.png");

	setupAnimations();
	playAnimation("RunRight");
}

void Player::setupAnimations() {
	addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
	addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {

}

void Player::moveLeft() {
	dx_ = -player_constants::WALK_SPEED;
	playAnimation("RunLeft");
	facing_ = LEFT;
}
void Player::moveRight() {
	dx_ = player_constants::WALK_SPEED;
	playAnimation("RunRight");
	facing_ = RIGHT;
}

void Player::stopMoving() {
	dx_ = 0.0f;
	playAnimation(facing_ == RIGHT ? "IdleRight" : "IdleLeft");

}

void Player::handleTileCollisions(std::vector<Rectangle> &others) {
	// Figure out what side the collision happened on and move the player accordingly
	for (int i = 0; i < others.size(); i++) {
		sides::Side collisionSide = Sprite::getCollisionSide(others[i]);
		if (collisionSide != sides::NONE) {
		// The y increases from 0 at the top to y at the bottom
		// It is not like the normal situation
		// Normal:                  Screen:  (0,0) ________x
		//           y|                           |
		//            |                           |
		//            |________x                 y|
		//        (0,0)
		// So it's y_ = others[i].getBottom() + 1; rather than y_ = others[i].getBottom() - 1;
		// As to y_ = others[i].getTop() - boundingBox_.getTop() - 1;
		// Draw a diagram to understand it
			switch (collisionSide) {
			case sides::TOP:
				y_ = others[i].getBottom() + 1; 
				dy_ = 0;
				printf("Collision at top\n");
				break;
			case sides::BOTTOM:
				y_ = others[i].getTop() - boundingBox_.getHeight() - 1;
				dy_ = 0;
				grounded_ = true;
				printf("Collision at bottom\n");
				break;
			case sides::LEFT:
				x_ = others[i].getRight() + 1;
				//dx_ = 0;
				printf("Collision at left\n");
				break;
			case sides::RIGHT:
				x_ = others[i].getLeft() - boundingBox_.getWidth() - 1;
				//dx_ = 0;
				printf("Collision at right\n");
				break;
			}
		}
	}
}

void Player::draw(Graphics& graphics) {
	AnimatedSprite::draw(graphics, x_, y_);
}

void Player::update(float elapsedTime) {
	// Apply gravity
	if (dy_ <= player_constants::GRAVITY_CAP) {
		dy_ += player_constants::GRAVITY * elapsedTime;
	}

	// Move by dx
	x_ += dx_ * elapsedTime;

	// Move by dy
	y_ += dy_ * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

const float Player::getX() const {
	return x_;
}

const float Player::getY() const {
	return y_;
}

Player ::~Player() {

}