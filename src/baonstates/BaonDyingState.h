/*
 * BaonDyingState.h
 *
 *  Created on: 25/06/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONDYINGSTATE_H_
#define BAONSTATES_BAONDYINGSTATE_H_

#include "BaonState.h"

class BaonDyingState : public BaonState{
public:
	BaonDyingState(bool flipped);
	virtual ~BaonDyingState();
	void Update(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);

private:
	static float STATE_TIME;
};

#endif /* BAONSTATES_BAONDYINGSTATE_H_ */
