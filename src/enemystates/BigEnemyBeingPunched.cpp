/*
 * BenderEnemyBeingPushed.cpp
 *
 *  Created on: 09/07/2015
 *      Author: Pedro2
 */

#include "BigEnemyBeingPunched.h"

BigEnemyBeingPushed::~BigEnemyBeingPushed() {
	delete t;
}

void BigEnemyBeingPushed::enter() {
	t->Restart();
	if(enemy->IsCollisionFromRight()){
		enemy->GetBody()->SetVelX(-400);
	}
	else{
		enemy->GetBody()->SetVelX(400);
	}
	askEnd = false;
}

void BigEnemyBeingPushed::exit() {
	enemy->GetBody()->SetVelX(0);
}

void BigEnemyBeingPushed::update(const float dt_) {
	if(t->Get() < 0.6){
		t->Update(dt_);
	}
	else{
		askEnd = true;
	}
}
