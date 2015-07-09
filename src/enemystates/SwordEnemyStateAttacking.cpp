/*
 * SwordEnemyStateAttacking.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyStateAttacking.h"

SwordEnemyStateAttacking::SwordEnemyStateAttacking(SwordEnemy* const enemy_) : StateSwordEnemy(enemy_) {}

void SwordEnemyStateAttacking::enter() {
	askEnd = false;
	enemy->GetBody()->SetVelX(0);
	enemy->SetAttackingSprite();
}

void SwordEnemyStateAttacking::exit() {}

void SwordEnemyStateAttacking::update(const float dt_) {
	enemy->GetSprite()->Update(dt_);

	if(enemy->GetSprite()->GetCurrentFrame() > 3){
		enemy->isDamage = true;
	}

	if(enemy->GetSprite()->GetCurrentFrame() >= 5){
		enemy->isDamage = false;
		askEnd = true;
	}
}
