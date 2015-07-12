/*
 * BigEnemyStateDying.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "BigEnemyStateDying.h"

BigEnemyStateDying::BigEnemyStateDying(BigEnemy* const enemy_) : StateBigEnemy(enemy_) {
	t = new Timer();
	dyingSound = new Sound("audio/sfx_enemy_fall.wav");
}

BigEnemyStateDying::~BigEnemyStateDying() {
	delete t;
	delete dyingSound;
}

void BigEnemyStateDying::enter() {
	askEnd = false;
	t->Restart();
	enemy->SetDyingSprite();
	enemy->GetBody()->SetVelX(0);
	enemy->GetBody()->clearForces();
	dyingSound->Play(0);
}

void BigEnemyStateDying::exit() {}

void BigEnemyStateDying::update(const float dt_) {
	if(t->Get() < 1){
		if(enemy->GetSprite()->GetCurrentFrame() < 2){
			enemy->GetSprite()->Update(dt_);
		}
		t->Update(dt_);
	}
	else{
		enemy->SetDead(true);
	}
}
