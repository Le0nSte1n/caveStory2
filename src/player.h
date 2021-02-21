#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "animatedSprite.h"
#include "globals.h"
class Player : public AnimatedSprite{
public:
	Player ();
	Player(Graphics& graphics, float x, float y);
	void draw(Graphics& graphics);
	void update(float elapsedTime);

	/* void moveLeft
	 * Moves the player left by -dx
	 */
	void moveLeft();

	/* void moveRight
	 * Moves the player right by dx
	 */
	void moveRight();

	/* void stopMoving
	 * Stops moving the player (keep the current facing direction)
	 */
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations(); 

	const float getX() const;
	const float getY() const;


	~Player ();

private:
	float dx_, dy_;
	Direction facing_;

	bool grounded_;	// be true if the player is on the ground, be false otherwise
};

#endif // !PLAYER_H

