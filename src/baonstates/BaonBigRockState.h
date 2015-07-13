/*
 * BaonBigRockState.h
 *
 *  Created on: 13/07/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONBIGROCKSTATE_H_
#define BAONSTATES_BAONBIGROCKSTATE_H_

#include <string>

#include "BaonState.h"
#include "../BigRock.h"
#include "../Engine/Timer.h"

class BaonBigRockState : public BaonState{
public:
	BaonBigRockState(bool flipped);
	virtual ~BaonBigRockState();

	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
private:
	BigRock* pedra;
	Timer* t;
};

#endif /* BAONSTATES_BAONBIGROCKSTATE_H_ */
