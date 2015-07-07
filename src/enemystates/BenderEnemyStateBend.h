/*
 * EnemyStateBend.h
 *
 *  Created on: 19/06/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYSTATEBEND_H_
#define ENEMYSTATES_BENDERENEMYSTATEBEND_H_

#include "../PedraBasico.h"
#include "StateEnemy.h"

class EnemyStateBend : public StateEnemy{
public:
	EnemyStateBend(Enemy* const enemy_);
	virtual ~EnemyStateBend();
	void enter();
	void exit();
	void update(const float dt_);
private:
	PedraBasico *pedra;
};

#endif /* ENEMYSTATES_BENDERENEMYSTATEBEND_H_ */