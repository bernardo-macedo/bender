/*
 * BaonDefenseStoneState.h
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONDEFENSESTONESTATE_H_
#define BAONSTATES_BAONDEFENSESTONESTATE_H_

#include <string>

#include "BaonState.h"
#include "../PedraDefesa.h"
#include "../Hud.h"

class BaonDefenseStoneState : public BaonState{
public:
	BaonDefenseStoneState(bool flipped);

	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
private:
	PedraDefesa *pedra;
};

#endif /* BAONSTATES_BAONDEFENSESTONESTATE_H_ */
