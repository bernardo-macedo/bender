/*
 * State.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include <cstdlib>
#include <ctime>

#include "State.h"
#include "InputManager.h"
#include "Game.h"

State::State() {
	quitRequested = false;
	srand(time(NULL));
}

State::~State(){
	objectArray.clear();
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::AddObject(GameObject* object){
	objectArray.emplace_back(object);
}
