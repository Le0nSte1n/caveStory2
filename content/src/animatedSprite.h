#pragma once
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

/* AnimatedSprite class
 * Holds logic for animating sprites
 * Animates sprites
 */

#include <string>
#include <map>
#include <vector>

#include "graphics.h"
#include "sprite.h"
#include "globals.h"

class AnimatedSprite :public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, 
		int width, int height, float posX, float posY, float timeToUpdate);

	/* void playAnimation
	 * Plays the animation provided if it's not already playing
	 *
	 * animation:	store animations by name, so to play one animation is to pass in the name of it
	 * once:		to decide whether the animation should paly once or loop
	 */
	void playAnimation(std::string animation, bool once = false);

	/* void update
	 * Updates the animated sprite (timer)
	 */
	void update(float elapsedTime);

	/* void draw
	 * Draws the sprite to the screen
	 */
	void draw(Graphics& graphics, int x, int y);

	~AnimatedSprite();

protected:
	double timeToUpdate_;	// the amount of time between the frames
	bool currentAnimationOnce_;	// whether an animation is played once
	std::string currentAnimation_;	// the name of the current animation

	/* void addAnimation
	 * Adds an animation to the map of animations for the aprite
	 * 
	 * frames:	the amount of frames that need to be cut out
	 * name:	the name of an animation
	 * offset:	the offset to add when calculating
	 * 
	 */
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	/* void resetAnimation
	 * Resets all animations associated with this sprite
	 */
	void resetAnimation();

	/* void stopAnimation
	 * Stops the animation
	 */
	void stopAnimation();

	/* void setVisible
	 * Changes the visibility of the animated sprite
	 */
	void setVisible(bool visible);

	/* void animationDone
	 * Logic that happens when an animation ends
	 */
	virtual void animationDone(std::string currentAnimation) = 0;

	/* void setupAnimations
	 * A required function that sets up all animations for a sprite
	 */
	virtual void setupAnimations() = 0;

private:
	// a map full of animations, the animations of which can be kept track of by name
	// the vector is actually filled with "small pixel rectangles" 
	// that can be grabed form MyChar.png piece by piece
	std::map<std::string, std::vector<SDL_Rect>> animations_;
	std::map<std::string, Vector2> offsets_;

	int frameIndex_;	// the index of an animation when playing it. 0, 1, 2, 0, 1, 2 or just 0, 1, 2, stop 
	double timeElapsed_;	// lasting time of a frame, will be compared with timeToUpdate to decide whether to go to next movement
	bool visible_;	// 

};

#endif // !ANIMATEDSPRITE_H
