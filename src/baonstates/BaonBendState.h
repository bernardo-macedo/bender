/*
 * BaonBendState.h
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#ifndef BAONBENDSTATE_H_
#define BAONBENDSTATE_H_

#include <string>

#include "BaonState.h"

class BaonBendState : public BaonState{
public:
	BaonBendState(bool flipped);
	void Update(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
};

#endif /* BAONBENDSTATE_H_ */
