/*
 * BigEnemyStateAttacking.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "BigEnemyStateAttacking.h"

BigEnemyStateAttacking::BigEnemyStateAttacking(BigEnemy* const enemy_) : StateBigEnemy(enemy_) {
	shoulderSwingSound = new Sound("audio/sfx_enemy_shoulder_swing.wav");
}

BigEnemyStateAttacking::~BigEnemyStateAttacking() {
	delete shoulderSwingSound;
}

void BigEnemyStateAttacking::enter() {
	askEnd = false;
	enemy->GetBody()->SetVelX(0);
	enemy->SetAttackingSprite();
	enemy->GetSprite()->SetFrameTime(0.05);
	shoulderSwingSound->Play(0);
	enemy->SetLastGivenAttack(EnemyAttack::SHOULDER);
}

void BigEnemyStateAttacking::exit() {
	enemy->GetSprite()->SetFrameTime(0.1);
}

void BigEnemyStateAttacking::update(const float dt_) {
	enemy->GetSprite()->Update(dt_);

	if(enemy->GetSprite()->GetCurrentFrame() >= 3){
		enemy->isDamage = true;
	}

	if(enemy->GetSprite()->GetCurrentFrame() >= 5){
		enemy->isDamage = false;
		askEnd = true;
	}
}
