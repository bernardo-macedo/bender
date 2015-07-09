/*
 * SwordEnemyStateDying.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyStateDying.h"

SwordEnemyStateDying::SwordEnemyStateDying(SwordEnemy* const enemy_) : StateSwordEnemy(enemy_) {
	t = new Timer();
}

SwordEnemyStateDying::~SwordEnemyStateDying() {
	delete t;
}

void SwordEnemyStateDying::enter() {
	askEnd = false;
	t->Restart();
	enemy->SetDyingSprite();
	enemy->GetBody()->SetVelX(0);
	enemy->GetBody()->clearForces();
}

void SwordEnemyStateDying::exit() {}

void SwordEnemyStateDying::update(const float dt_) {
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
