/*
 * BenderEnemyBeingPushed.cpp
 *
 *  Created on: 09/07/2015
 *      Author: Pedro2
 */

#include "BenderEnemyBeingPushed.h"

EnemyBeingPushed::~EnemyBeingPushed() {
	// TODO Auto-generated destructor stub
}

void EnemyBeingPushed::enter() {
	t->Restart();
	if(enemy->IsCollisionFromRight()){
		enemy->GetBody()->SetVelX(-400);
	}
	else{
		enemy->GetBody()->SetVelX(400);
	}
	askEnd = false;
}

void EnemyBeingPushed::exit() {
	enemy->GetBody()->SetVelX(0);
}

void EnemyBeingPushed::update(const float dt_) {
	if(t->Get() < 0.6){
		t->Update(dt_);
	}
	else{
		askEnd = true;
	}
}
