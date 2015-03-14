/*
 * State.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "State.h"

State::State() {
	quitRequested = false;
	bg = new Sprite("ocean.jpg");
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Update() {
	if(SDL_QuitRequested()){
		quitRequested = true;
	}
}

void State::Render(SDL_Renderer* renderer) {
	bg->Render(0, 0);
}
