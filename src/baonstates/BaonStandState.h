/*
 * BaonStandState.h
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#ifndef BAONSTANDSTATE_H_
#define BAONSTANDSTATE_H_

#include <string>

#include "BaonState.h"

class BaonStandState : public BaonState{
public:
	BaonStandState(bool flipped);
	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string name);
};

#endif /* BAONSTANDSTATE_H_ */
