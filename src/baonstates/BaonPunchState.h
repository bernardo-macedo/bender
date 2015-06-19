/*
 * BaonPunchState.h
 *
 *  Created on: 27/05/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONPUNCHSTATE_H_
#define BAONSTATES_BAONPUNCHSTATE_H_

#include <string>

#include "BaonState.h"
#include "../PedraBasico.h"
class Timer;

class BaonPunchState : public BaonState{
public:
	BaonPunchState(bool flipped);
	void Update(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
private:
	PedraBasico *pedra;
	bool soltouPedra;
};

#endif /* BAONSTATES_BAONPUNCHSTATE_H_ */
