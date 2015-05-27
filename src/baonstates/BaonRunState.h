/*
 * BaonRunState.h
 *
 *  Created on: 27/05/2015
 *      Author: Pedro2
 */

#ifndef BAONRUNSTATE_H_
#define BAONRUNSTATE_H_

#include <string>

#include "BaonState.h"

class BaonRunState : public BaonState{
public:
	BaonRunState(bool flipped);
	void Update(Baon* baon, BaonStateManager* sm);
	bool Is(std::string state);
private:
	bool executed;
};

#endif /* BAONRUNSTATE_H_ */
