#pragma once
#ifndef GAME_H
#define GAME_H

/* Game class
 * This class holds all information for our main game loop
 */

#include <SDL.h>
#include <string>

#include "graphics.h"
#include "input.h"
#include "player.h"
#include "level.h"

class Graphics;

class Game{
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics& graphics);
	void update(float elapsedTime);

	Player player_;
	Level level_;
};



#endif // !GAME_H
