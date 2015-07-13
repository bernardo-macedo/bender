/*
 * BigEnemyStateTakeDamage.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "BigEnemyStateTakeDamage.h"

BigEnemyStateTakeDamage::BigEnemyStateTakeDamage(BigEnemy* const enemy_) : StateBigEnemy(enemy_) {}

void BigEnemyStateTakeDamage::enter() {
	askEnd = false;
	enemy->SetTakingDamageSprite();
	enemy->GetSprite()->SetFrameTime(0.2);
	if(enemy->IsCollisionFromRight()){
		enemy->GetBody()->SetVelX(-100);
		enemy->GetBody()->ApplyForce(new Force("resistance", 150, 0));
	}
	else{
		enemy->GetBody()->SetVelX(100);
		enemy->GetBody()->ApplyForce(new Force("resistance", -150, 0));
	}
}

void BigEnemyStateTakeDamage::exit() {
	enemy->GetBody()->SetVelX(0);
	enemy->GetBody()->removeForce("resistance");
	enemy->SetTakingDamage(false);
	enemy->GetSprite()->SetFrameTime(0.1);
	if(enemy->GetHP() <= 0){
		enemy->SetDying(true);
	}
}

void BigEnemyStateTakeDamage::update(const float dt_) {
	if(enemy->GetSprite()->GetCurrentFrame() < 4) {
		enemy->GetSprite()->Update(dt_);
	} else{
		askEnd = true;
	}
}
