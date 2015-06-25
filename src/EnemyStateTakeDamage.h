/*
 * EnemyStateTakeDamage.h
 *
 *  Created on: 25/06/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATETAKEDAMAGE_H_
#define ENEMYSTATETAKEDAMAGE_H_

#include "StateEnemy.h"

class EnemyStateTakeDamage : public StateEnemy{
public:
	EnemyStateTakeDamage(Enemy* const enemy_);

	void enter();
	void exit();
	void update(const float dt_);
};

#endif /* ENEMYSTATETAKEDAMAGE_H_ */
