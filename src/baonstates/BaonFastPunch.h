/*
 * BaonFastPunch.h
 *
 *  Created on: 01/07/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONFASTPUNCH_H_
#define BAONSTATES_BAONFASTPUNCH_H_

#include <iostream>

#include "BaonState.h"
#include "../Engine/Sound.h"

class BaonFastPunch : public BaonState {
public:
	BaonFastPunch(bool flipped);
	virtual ~BaonFastPunch();

	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);

private:
	Sound *fastPunchSound;
};

#endif /* BAONSTATES_BAONFASTPUNCH_H_ */
