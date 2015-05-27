#include "EnemyStatePatrolling.h"
#include <cfloat>
#include <iostream>

void EnemyStatePatrolling::enter(){
	
}

void EnemyStatePatrolling::exit(){
	enemy->Time()->Restart();
}

void EnemyStatePatrolling::update(const float dt_){
	
	// Patrol.
	enemy->Run(false);
	if(enemy->Time()->Get() > 3){
		enemy->changeState(Enemy::enemyStates::FOLLOW);
	}
	//enemy->getSprite()->
}

EnemyStatePatrolling::EnemyStatePatrolling(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}
