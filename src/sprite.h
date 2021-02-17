#pragma once
#ifndef SPRITE_H
#define SPRITE_H

/* Sprite class
 * Holds all information for individual sprites
 */

#include <SDL.h>
#include <string>

#include "graphics.h"

class Sprite{
public:
	Sprite();
	Sprite(Graphics& graphics, const std::string& filePath, int sourceX, 
		int sourceY, int width, int height, float posX, float posY);

	/* virtual ~Sprite & virtual ~Sprite
	 * player classed and enemy classed will all be derived from this class
	 * so its deconstructor method needs to be virtual
	 * it is the same with the update method
	 */
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics& graphics, int x, int y);

protected:
	SDL_Rect sourceRect_;
	SDL_Texture* sprite_sheet_;
	float x_, y_;

private:

};

#endif // !SPRITE_H

