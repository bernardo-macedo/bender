/*
 * BenderEnemyBeingPushed.h
 *
 *  Created on: 09/07/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_
#define ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_

#include "StateBigEnemy.h"
#include "../Engine/Timer.h"

class BigEnemyBeingPushed : public StateBigEnemy{
public:
	BigEnemyBeingPushed(BigEnemy* const enemy_) : StateBigEnemy(enemy_){
		t = new Timer();
	}
	virtual ~BigEnemyBeingPushed();

	void enter();
	void exit();
	void update(const float dt_);
private:
	Timer* t;
};

#endif /* ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_ */
