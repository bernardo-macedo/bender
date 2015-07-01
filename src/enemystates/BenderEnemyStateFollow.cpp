#include "BenderEnemyStateFollow.h"
#include <cfloat>
#include <iostream>

void EnemyStateFollow::enter(){
	
}

void EnemyStateFollow::exit(){
	enemy->Time()->Restart();
}

void EnemyStateFollow::update(const float dt_){
	
	// Follow.
	
}

EnemyStateFollow::EnemyStateFollow(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}
