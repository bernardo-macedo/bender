/*
 * BenderEnemyBeingPushed.cpp
 *
 *  Created on: 09/07/2015
 *      Author: Pedro2
 */

#include "SwordEnemyBeingPunched.h"

SwordEnemyBeingPushed::~SwordEnemyBeingPushed() {
	// TODO Auto-generated destructor stub
}

void SwordEnemyBeingPushed::enter() {
	t->Restart();
	if(enemy->IsCollisionFromRight()){
		enemy->GetBody()->SetVelX(400);
	}
	else{
		enemy->GetBody()->SetVelX(-400);
	}
	askEnd = false;
}

void SwordEnemyBeingPushed::exit() {
	enemy->GetBody()->SetVelX(0);
}

void SwordEnemyBeingPushed::update(const float dt_) {
	if(t->Get() < 0.6){
		t->Update(dt_);
	}
	else{
		askEnd = true;
	}
}
