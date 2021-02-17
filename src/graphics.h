#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL.h>
#include <SDL_image.h>

/* Graphics class
 * Hold all information dealing with graphics for the game
 */

#include <map>
#include <string>
#include <SDL.h>

class Graphics {
public:
	Graphics();
	~Graphics();

	/* SDL_Surcade* loadImage
     * Loads an image into the spriteSheets_ map if it doesn't already exists
	 * As a result each image will only be loaded once
	 * Return the image from the map regardless of whether or not it was just loaded
     */
	SDL_Surface* loadImage(const std::string& filePath);

	/* void blitSurface
	 * Draws a texture to a certain part of the screen
	 */
	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/* void flip
     * Renders everything to the screen
     */
	void flip();

	/* void clear
	 * Clears the screen.(every time before drawing)
	 */
	void clear();

	/* SDL_Renderer* getRenderer
	 * Returns the renderer for use
	 */
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* window_;	// where we are drawing
	SDL_Renderer* renderer_;	// what actually does the drawing

	/* spriteSheets_
	 * hold in memory in the graphics object every sprite sheet that has been loaded into the game
	 */
	std::map<std::string, SDL_Surface*> spriteSheets_;	
};

#endif	// !GRAPHICS_H