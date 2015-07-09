/*
 * EnemyStateDying.cpp
 *
 *  Created on: 26/06/2015
 *      Author: Pedro2
 */

#include "BenderEnemyStateDying.h"

EnemyStateDying::EnemyStateDying(Enemy* const enemy_) : StateEnemy(enemy_) {
	t = new Timer();
	dyingSound = new Sound("audio/sfx_enemy_fall.wav");
}

EnemyStateDying::~EnemyStateDying() {
	delete t;
	delete dyingSound;
}

void EnemyStateDying::enter(){
	askEnd = false;
	t->Restart();
	dyingSound->Play(0);
	enemy->GetSprite()->SetFrameWidth(33);
	enemy->GetSprite()->SetFrameHeight(50);
	enemy->GetSprite()->SetFrameTime(0.1);
	enemy->GetSprite()->SetLine(5, 50);
	enemy->GetBody()->SetVelX(0);
	enemy->GetBody()->clearForces();
}

void EnemyStateDying::exit(){
}

void EnemyStateDying::update(const float dt_){
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

