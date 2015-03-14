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

void State::Render() {
	bg->Render(0, 0);
}
