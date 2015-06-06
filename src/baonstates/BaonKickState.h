/*
 * BaonKickState.h
 *
 *  Created on: 27/05/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONKICKSTATE_H_
#define BAONSTATES_BAONKICKSTATE_H_

#include <string>

#include "BaonState.h"

class Timer;

class BaonKickState : public BaonState{
public:
	BaonKickState(bool flipped);

	void Update(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
};

#endif /* BAONSTATES_BAONKICKSTATE_H_ */
