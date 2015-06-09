/*
 * BaonTakeHitState.h
 *
 *  Created on: 09/06/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONTAKEHITSTATE_H_
#define BAONSTATES_BAONTAKEHITSTATE_H_

#include "BaonState.h"

class BaonTakeHitState : public BaonState{
public:
	BaonTakeHitState(bool flipped);

	void Update(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
};

#endif /* BAONSTATES_BAONTAKEHITSTATE_H_ */
