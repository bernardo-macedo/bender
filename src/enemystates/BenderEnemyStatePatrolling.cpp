#include "BenderEnemyStatePatrolling.h"
#include <cfloat>
#include <iostream>

void EnemyStatePatrolling::enter(){
	patrollDistance = enemy->GetSpawnX();
	patrollMaxDistance = patrollDistance + 50;

	enemy->GetSprite()->SetFrameHeight(50);
	enemy->GetSprite()->SetFrameWidth(36);
	enemy->GetSprite()->SetFrameCount(6);
	enemy->GetSprite()->SetLine(1, 50);
	isLeft = false;
}

void EnemyStatePatrolling::exit(){
	enemy->GetTimer()->Restart();
}

void EnemyStatePatrolling::update(const float dt_){
	
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
	else{
		
	}

	enemy->Run(isLeft);
}

EnemyStatePatrolling::EnemyStatePatrolling(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}
