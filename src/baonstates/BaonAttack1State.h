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
#include "../Hud.h"
#include "../Engine/Sound.h"

class BaonAttack1State : public BaonState, public RockDeathListener {
public:
	BaonAttack1State(bool flipped);
	virtual ~BaonAttack1State();
	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
	virtual void ResolveDeadReferences(int id);
	void OnRockDead();
private:
	PedraBasico* pedra;
	bool justJumped, canExecute, soundPlayed;
	Sound *bendJumpSound;
};

#endif /* BAONATTACK1STATE_H_ */
