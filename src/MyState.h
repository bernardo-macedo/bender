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
public:
	virtual ~MyState();

	void OnRender();
	void Setup();
};

#endif /* MYSTATE_H_ */
