/*
 * BenderEnemyBeingPushed.h
 *
 *  Created on: 09/07/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_
#define ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_

#include "StateEnemy.h"
#include "../Engine/Timer.h"

class EnemyBeingPushed : public StateEnemy{
public:
	EnemyBeingPushed(Enemy* const enemy_) : StateEnemy(enemy_){
		t = new Timer();
	}
	virtual ~EnemyBeingPushed();

	void enter();
	void exit();
	void update(const float dt_);
private:
	Timer* t;
};

#endif /* ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_ */
