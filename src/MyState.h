/*
 * MyState.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef MYSTATE_H_
#define MYSTATE_H_

#include "Engine/State.h"
#include "Drone.h"

class MyState: public State {
private:
	bool applied;
public:
	MyState();
	virtual ~MyState();

	void OnRender();
	void Setup();
	void OnMouseDown(SDL_Event event);
};

#endif /* MYSTATE_H_ */
