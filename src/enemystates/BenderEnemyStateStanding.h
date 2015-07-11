/*
 * BenderEnemyStateStanding.h
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYSTATESTANDING_H_
#define ENEMYSTATES_BENDERENEMYSTATESTANDING_H_

#include "StateEnemy.h"

class BenderEnemyStateStanding : public StateEnemy{
public:
	BenderEnemyStateStanding(Enemy* const enemy_) : StateEnemy(enemy_){
		askEnd = false;
	}

	void enter();
	void exit();
	void update(const float dt_);
};

#endif /* ENEMYSTATES_BENDERENEMYSTATESTANDING_H_ */
