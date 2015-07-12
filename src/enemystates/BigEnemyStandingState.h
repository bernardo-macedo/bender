/*
 * BigEnemyStandingState.h
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BigENEMYSTANDINGSTATE_H_
#define ENEMYSTATES_BigENEMYSTANDINGSTATE_H_

#include "../BigEnemy.h"
#include "StateBigEnemy.h"
#include "../Engine/Timer.h"

class BigEnemyStandingState : public StateBigEnemy{
public:
	BigEnemyStandingState(BigEnemy* const enemy_)
		: StateBigEnemy(enemy_){
		askEnd = false;
		t = new Timer();
	}

	virtual ~BigEnemyStandingState();

	void enter();
	void exit();
	void update(const float dt_);

private:
	Timer* t;
};

#endif /* ENEMYSTATES_BigENEMYSTANDINGSTATE_H_ */
