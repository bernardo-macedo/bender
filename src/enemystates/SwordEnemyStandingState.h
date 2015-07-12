/*
 * SwordEnemyStandingState.h
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_SWORDENEMYSTANDINGSTATE_H_
#define ENEMYSTATES_SWORDENEMYSTANDINGSTATE_H_

#include "../SwordEnemy.h"
#include "StateSwordEnemy.h"
#include "../Engine/Timer.h"

class SwordEnemyStandingState : public StateSwordEnemy{
public:
	SwordEnemyStandingState(SwordEnemy* const enemy_)
		: StateSwordEnemy(enemy_){
		askEnd = false;
		t = new Timer();
	}

	virtual ~SwordEnemyStandingState();

	void enter();
	void exit();
	void update(const float dt_);

private:
	Timer* t;
};

#endif /* ENEMYSTATES_SWORDENEMYSTANDINGSTATE_H_ */
