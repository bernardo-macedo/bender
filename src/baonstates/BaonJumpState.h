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

	void Update(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
};

#endif /* BAONJUMPSTATE_H_ */
