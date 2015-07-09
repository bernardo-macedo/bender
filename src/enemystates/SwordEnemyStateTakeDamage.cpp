/*
 * SwordEnemyStateTakeDamage.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyStateTakeDamage.h"

SwordEnemyStateTakeDamage::SwordEnemyStateTakeDamage(SwordEnemy* const enemy_) : StateSwordEnemy(enemy_) {}

void SwordEnemyStateTakeDamage::enter() {
	askEnd = false;
	enemy->SetTakingDamageSprite();
	if(enemy->IsCollisionFromRight()){
		enemy->GetBody()->SetVelX(-100);
		enemy->GetBody()->ApplyForce(new Force("resistance", 150, 0));
	}
	else{
		enemy->GetBody()->SetVelX(100);
		enemy->GetBody()->ApplyForce(new Force("resistance", -150, 0));
	}
}

void SwordEnemyStateTakeDamage::exit() {
	enemy->GetBody()->SetVelX(0);
	enemy->GetBody()->clearForces();
	enemy->SetTakingDamage(false);
	enemy->GetSprite()->SetFrameTime(0.1);
	if(enemy->GetHP() <= 0){
		enemy->SetDying(true);
	}
}

void SwordEnemyStateTakeDamage::update(const float dt_) {
	if(enemy->GetSprite()->GetCurrentFrame() < 4) {
		enemy->GetSprite()->Update(dt_);
	} else{
		askEnd = true;
	}
}
