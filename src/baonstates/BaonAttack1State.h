/*
 * BaonAttack1State.h
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#ifndef BAONATTACK1STATE_H_
#define BAONATTACK1STATE_H_

#include <string>

#include "BaonState.h"
#include "../PedraBasico.h"

class BaonAttack1State : public BaonState{
public:
	BaonAttack1State(bool flipped);
	void Update(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
private:
	PedraBasico* pedra;
	bool justJumped, canExecute;
};

#endif /* BAONATTACK1STATE_H_ */
