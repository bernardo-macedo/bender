/*
 * BaonSpikeStoneState.h
 *
 *  Created on: 07/07/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONSPIKESTONESTATE_H_
#define BAONSTATES_BAONSPIKESTONESTATE_H_

#include <string>

#include "BaonState.h"
#include "../SpikeStone.h"
#include "../Hud.h"

class BaonSpikeStoneState : public BaonState{
public:
	BaonSpikeStoneState(bool flipped);
	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
private:
	SpikeStone* pedra;
};

#endif /* BAONSTATES_BAONSPIKESTONESTATE_H_ */
