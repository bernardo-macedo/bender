/*
 * Game.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GAME_H_
#define ENGINE_GAME_H_

#include "State.h"
#include "Checkpoint.h"
#include "Physics/Physic.h"
#include "SDL_Wrapper.h"
#include <stack>

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;
	static Game* instance;
	int frameStart;
	float dt;
	Physic *physic;
	Checkpoint *checkpoint;

	std::stack<std::unique_ptr<State>> stateStack;

	void CalculaDeltaTime();
	void init();
public:
	static int SCALE;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	Game(std::string title, int width, int height);
	virtual ~Game();

	void Run();
	SDL_Renderer* GetRenderer();
	State* GetCurrentState();
	static Game* GetInstance();
	float GetDeltaTime();
	void Push(State* state);
	void SetCheckpoint(Checkpoint* checkpoint);
	Checkpoint* GetCheckpoint();
};

#endif /* ENGINE_GAME_H_ */
