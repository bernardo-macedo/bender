/*
 * EnemyStatePunch.cpp
 *
 *  Created on: 04/06/2015
 *      Author: Pedro2
 */

#include "BenderEnemyStatePunch.h"

EnemyStatePunch::EnemyStatePunch(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

void EnemyStatePunch::enter() {
	enemy->GetBody()->SetVelX(0);
	askEnd = false;
	enemy->GetSprite()->SetFrameHeight(50);
	enemy->GetSprite()->SetFrameWidth(36);
	enemy->GetSprite()->SetFrameCount(5);
	enemy->GetSprite()->SetLine(3, 50);
}

void EnemyStatePunch::exit() {
}

void EnemyStatePunch::update(const float dt_) {
	enemy->GetSprite()->Update(dt_);

	if(enemy->GetSprite()->GetCurrentFrame() > 3){
		enemy->isDamage = true;
	}

	if(enemy->GetSprite()->GetCurrentFrame() >= 5){
		enemy->isDamage = false;
		askEnd = true;
	}
}
