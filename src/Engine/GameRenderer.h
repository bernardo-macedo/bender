/*
 * GameRenderer.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GAMERENDERER_H_
#define ENGINE_GAMERENDERER_H_
#include <iostream>

#include "SDL.h"

#include "State.h"
#include "Exceptions.h"

class GameRenderer {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	static GameRenderer* instance;

	void init();
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	GameRenderer(std::string title, int width, int height);
	virtual ~GameRenderer();

	void Run();
	SDL_Renderer* GetRenderer();
	State* GetState();
	static GameRenderer* GetInstance();
};

#endif /* ENGINE_GAMERENDERER_H_ */
