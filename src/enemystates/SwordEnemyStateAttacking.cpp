/*
 * SwordEnemyStateAttacking.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyStateAttacking.h"

SwordEnemyStateAttacking::SwordEnemyStateAttacking(SwordEnemy* const enemy_) : StateSwordEnemy(enemy_) {
	swordSwingSound = new Sound("audio/sfx_enemy_sword_swing.wav");
}

SwordEnemyStateAttacking::~SwordEnemyStateAttacking() {
	delete swordSwingSound;
}

void SwordEnemyStateAttacking::enter() {
	askEnd = false;
	enemy->GetBody()->SetVelX(0);
	enemy->SetAttackingSprite();
	swordSwingSound->Play(0);
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
