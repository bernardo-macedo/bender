/*
 * State.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_STATE_H_
#define ENGINE_STATE_H_

#include "SDL.h"
#include "Sprite.h";

class State {
private:
	Sprite* bg;
	bool quitRequested;
public:
	State();

	bool QuitRequested();
	void Update();
	void Render(SDL_Renderer* renderer);
};

#endif /* ENGINE_STATE_H_ */
