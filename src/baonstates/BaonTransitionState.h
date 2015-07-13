/*
 * BaonTransitionState.h
 *
 *  Created on: Jul 13, 2015
 *      Author: -Bernardo
 */

#ifndef BAONSTATES_BAONTRANSITIONSTATE_H_
#define BAONSTATES_BAONTRANSITIONSTATE_H_

#include "BaonState.h"

class BaonTransitionState  : public BaonState {
public:
	BaonTransitionState(bool flipped);
	virtual ~BaonTransitionState();
	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);

private:
	bool flipped;
};

#endif /* BAONSTATES_BAONTRANSITIONSTATE_H_ */
