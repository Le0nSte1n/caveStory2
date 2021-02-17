#include "graphics.h"

#include "globals.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_WIDTH, 0, &window_, &renderer_);
	SDL_SetWindowTitle(window_, "CaveStory");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(window_);
}

SDL_Surface* Graphics::loadImage(const std::string& filePath) {
	if (spriteSheets_.count(filePath) == 0) {
		// never be loaded yet
		spriteSheets_[filePath] = IMG_Load(filePath.c_str());
	}
	return spriteSheets_[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(renderer_, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
	SDL_RenderPresent(renderer_);
}

void Graphics::clear() {
	SDL_RenderClear(renderer_);
}

SDL_Renderer* Graphics::getRenderer() const {
	return renderer_;
}