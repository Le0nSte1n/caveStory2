#include "player.h"

namespace player_constants{
	const float WALK_SPEED = 0.2f;

	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player() {

}

Player::Player(Graphics& graphics, float x, float y) :
	AnimatedSprite(graphics, "content\\sprites\\MyChar.png", 0, 0, 16, 16, x, y, 100),
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