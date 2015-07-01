/*
 * EnemyStateTakeDamage.h
 *
 *  Created on: 25/06/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYSTATETAKEDAMAGE_H_
#define ENEMYSTATES_BENDERENEMYSTATETAKEDAMAGE_H_

#include "StateEnemy.h"

class EnemyStateTakeDamage : public StateEnemy{
public:
	EnemyStateTakeDamage(Enemy* const enemy_);

	void enter();
	void exit();
	void update(const float dt_);
};

#endif /* ENEMYSTATES_BENDERENEMYSTATETAKEDAMAGE_H_ */
