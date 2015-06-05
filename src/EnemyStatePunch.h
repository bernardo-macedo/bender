/*
 * EnemyStatePunch.h
 *
 *  Created on: 04/06/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATEPUNCH_H_
#define ENEMYSTATEPUNCH_H_

#include "StateEnemy.h"

class EnemyStatePunch : public StateEnemy{
public:
	EnemyStatePunch(Enemy* const enemy_);
	void enter();
	void exit();
	void update(const float dt_);
};

#endif /* ENEMYSTATEPUNCH_H_ */
