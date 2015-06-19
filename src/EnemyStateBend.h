/*
 * EnemyStateBend.h
 *
 *  Created on: 19/06/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATEBEND_H_
#define ENEMYSTATEBEND_H_

#include "PedraBasico.h"
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

#endif /* ENEMYSTATEBEND_H_ */
