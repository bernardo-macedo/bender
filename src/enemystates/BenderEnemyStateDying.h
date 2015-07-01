/*
 * EnemyStateDying.h
 *
 *  Created on: 26/06/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYSTATEDYING_H_
#define ENEMYSTATES_BENDERENEMYSTATEDYING_H_

#include "StateEnemy.h"
#include "../Engine/Timer.h"

class EnemyStateDying : public StateEnemy{
public:
	EnemyStateDying(Enemy* const enemy_);
	virtual ~EnemyStateDying();
	void enter();
	void exit();
	void update(const float dt_);
private:
	Timer* t;
};

#endif /* ENEMYSTATES_BENDERENEMYSTATEDYING_H_ */
