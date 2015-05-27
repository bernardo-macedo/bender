/*
 * BaonFallingState.h
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#ifndef BAONFALLINGSTATE_H_
#define BAONFALLINGSTATE_H_

#include <string>

#include "BaonState.h"

class BaonFallingState : public BaonState{
public:
	BaonFallingState(bool flipped);
	void Update(Baon* baon, BaonStateManager* sm);
	bool Is(std::string state);
};

#endif /* BAONFALLINGSTATE_H_ */
