/*
 * SwordEnemyStatePatrolling.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyStatePatrolling.h"

SwordEnemyStatePatrolling::SwordEnemyStatePatrolling(SwordEnemy* const enemy_) : StateSwordEnemy(enemy_) {}

void SwordEnemyStatePatrolling::enter() {
	patrollDistance = enemy->GetSpawnX();
	patrollMaxDistance = patrollDistance + 50;

	enemy->SetWalkSprite();
	isLeft = false;
}

void SwordEnemyStatePatrolling::exit() {
	enemy->GetTimer()->Restart();
}

void SwordEnemyStatePatrolling::update(const float dt_) {
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
		};
	}

	enemy->Walk(isLeft);
}
