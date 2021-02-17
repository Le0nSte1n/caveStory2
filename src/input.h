#pragma once
#ifndef INPUT_H
#define INPUT_H

/* Input class
 * Keep track of keyboard state
 */

#include <map>
#include <SDL.h>

class Input{
public:
	Input();
	~Input();
	void beginNewFrame();
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);
	bool wasKeyPressed(SDL_Scancode key);	// pass in a key and this func will tell whether it was pressed
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
private:
	std::map<SDL_Scancode, bool> heldKeys_;	// hold what keys are currently being held
	std::map<SDL_Scancode, bool> pressedKeys_;
	std::map<SDL_Scancode, bool> releasedKeys_;
};


#endif // !INPUT_H
