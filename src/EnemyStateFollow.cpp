#include "EnemyStateFollow.h"
#include <cfloat>
#include <iostream>

void EnemyStateFollow::enter(){
	
}

void EnemyStateFollow::exit(){
	enemy->Time()->Restart();
}

void EnemyStateFollow::update(const float dt_){
	
	// Patrol.
	enemy->Run(true);
	if(enemy->Time()->Get() > 3){
		enemy->changeState(Enemy::enemyStates::PATROLLING);
	}
	//enemy->getSprite()->
}

EnemyStateFollow::EnemyStateFollow(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}
