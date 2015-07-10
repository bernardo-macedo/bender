/*
 * BenderEnemyBeingPushed.h
 *
 *  Created on: 09/07/2015
 *      Author: Pedro2
 */

#ifndef ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_
#define ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_

#include "StateSwordEnemy.h"
#include "../Engine/Timer.h"

class SwordEnemyBeingPushed : public StateSwordEnemy{
public:
	SwordEnemyBeingPushed(SwordEnemy* const enemy_) : StateSwordEnemy(enemy_){
		t = new Timer();
	}
	virtual ~SwordEnemyBeingPushed();

	void enter();
	void exit();
	void update(const float dt_);
private:
	Timer* t;
};

#endif /* ENEMYSTATES_BENDERENEMYBEINGPUSHED_H_ */
