/*
 * BigEnemyStatePatrolling.cpp
 *
 *  Created on: Jul 12, 2015
 *      Author: -Bernardo
 */

#include "BigEnemyStatePatrolling.h"

BigEnemyStatePatrolling::BigEnemyStatePatrolling(BigEnemy* const enemy_) : StateBigEnemy(enemy_){
	isLeft = false;
	patrollDistance = 0;
	patrollMaxDistance = 0;
}

void BigEnemyStatePatrolling::enter() {
	patrollDistance = enemy->GetSpawnX();
	patrollMaxDistance = patrollDistance + 50;

	enemy->SetWalkSprite();
	isLeft = false;
}

void BigEnemyStatePatrolling::exit() {
	enemy->GetTimer()->Restart();
}

void BigEnemyStatePatrolling::update(const float dt_) {
	// Patrol.
	patrollDistance = enemy->GetBody()->GetX();
	enemy->GetSprite()->Update(dt_);

	float patrollDx = patrollMaxDistance - patrollDistance;
	if(abs(patrollDx) > 100.0){
		if(patrollDx > 0.0){
			isLeft = false;
		}
		else{
			isLeft = true;
		}
	}
	enemy->Run(isLeft);
}
