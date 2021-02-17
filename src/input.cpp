#include "input.h"

// This function gets called at the beginging of each new frame
// to reset the keys that are no longer relevent
void Input::beginNewFrame() {
	pressedKeys_.clear();
	releasedKeys_.clear();
}

// This function gets called when a key is released
void Input::keyUpEvent(const SDL_Event& event) {
	pressedKeys_[event.key.keysym.scancode] = true;
	heldKeys_[event.key.keysym.scancode] = false;	// be careful here
}

// This function gets called when a key has been pressed
void Input::keyDownEvent(const SDL_Event& event) {
	pressedKeys_[event.key.keysym.scancode] = true;
	heldKeys_[event.key.keysym.scancode] = true;
}

// Check if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
	return pressedKeys_[key];
}

// Check if a certain key was released during the current frame
bool Input::wasKeyReleased(SDL_Scancode key) {
	return releasedKeys_[key];
}

// Check if a certain key is currently held
bool Input::isKeyHeld(SDL_Scancode key) {
	return heldKeys_[key];
}

Input::Input() {

}

Input::~Input() {

}