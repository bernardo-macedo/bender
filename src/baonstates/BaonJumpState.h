/*
 * BaonJumpState.h
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#ifndef BAONJUMPSTATE_H_
#define BAONJUMPSTATE_H_

#include <string>

#include "BaonState.h"

class BaonJumpState : public BaonState{
public:
	BaonJumpState(bool flipped);

	void Update(Baon* baon, BaonStateManager* sm);
	bool Is(std::string state);
private:
	bool executed;

};

#endif /* BAONJUMPSTATE_H_ */
