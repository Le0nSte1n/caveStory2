#include "graphics.h"



Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &window_, &renderer_);
	SDL_SetWindowTitle(window_, "CaveStory");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
}

SDL_Surface* Graphics::loadImage(const std::string& filePath) {
	if (spriteSheets_.count(filePath) == 0) {
		// never be loaded yet
		char ch[260];
		_getcwd(ch, 260);
		std::string pwd(ch), fPath = filePath;
		//std::cout << pwd << std::endl;
		if (fPath.substr(0, 3) == "../") {
			fPath.erase(0, 3);
			fPath = "content/" + fPath;
		}
		for (int i = 0; i < pwd.size(); i++) {
			if (pwd[i] == '\\')
				pwd[i] = '/';
		}
		pwd = pwd + "/" + fPath;
		//std::cout << pwd.c_str() << std::endl;
		spriteSheets_[filePath] = IMG_Load(pwd.c_str());
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