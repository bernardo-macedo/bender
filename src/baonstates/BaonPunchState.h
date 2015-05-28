/*
 * BaonPunchState.h
 *
 *  Created on: 27/05/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONPUNCHSTATE_H_
#define BAONSTATES_BAONPUNCHSTATE_H_

#include <string>

#include "BaonState.h"

class Timer;

class BaonPunchState : public BaonState{
public:
	BaonPunchState(bool flipped);
	void Update(Baon* baon, BaonStateManager* sm, float dt);
	bool Is(std::string state);
private:
	int count;
	Timer* t;
};

#endif /* BAONSTATES_BAONPUNCHSTATE_H_ */
