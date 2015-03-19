/*
 * Game.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_

#include "State.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	static Game* instance;

	void init();
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	Game(std::string title, int width, int height);
	virtual ~Game();

	void Run();
	SDL_Renderer* GetRenderer();
	State* GetState();
	static Game* GetInstance();
};

#endif /* ENGINE_GAME_H_ */
