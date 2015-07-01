/*
 * EnemyStatePunch.h
 *
 *  Created on: 04/06/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYSTATEPUNCH_H_
#define ENEMYSTATES_BENDERENEMYSTATEPUNCH_H_

#include "StateEnemy.h"

class EnemyStatePunch : public StateEnemy{
public:
	EnemyStatePunch(Enemy* const enemy_);
	void enter();
	void exit();
	void update(const float dt_);
};

#endif /* ENEMYSTATES_BENDERENEMYSTATEPUNCH_H_ */
