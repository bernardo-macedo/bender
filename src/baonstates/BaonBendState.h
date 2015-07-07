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
#include "../BendHUD.h"

class BaonBendState : public BaonState{
public:
	BaonBendState(bool flipped);
	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
private:
	int bendKey[4];
	BendHUD* bendHUD;
	unsigned int countBend;
};

#endif /* BAONBENDSTATE_H_ */
