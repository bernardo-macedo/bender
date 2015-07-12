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
#include "../Engine/Sound.h"

class BaonRunState : public BaonState{
public:
	BaonRunState(bool flipped);
	virtual ~BaonRunState();
	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);

private:
	Sound* startRunningSound;
};

#endif /* BAONRUNSTATE_H_ */
