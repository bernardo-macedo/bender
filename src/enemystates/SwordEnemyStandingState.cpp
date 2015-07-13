/*
 * SwordEnemyStandingState.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#include "SwordEnemyStandingState.h"

void SwordEnemyStandingState::enter() {
	enemy->GetSprite()->SetFrameWidth(38);
	enemy->GetSprite()->SetFrameHeight(60);
	enemy->GetSprite()->SetFrameCount(2);
	enemy->GetSprite()->SetLine(0, 60);
	enemy->GetBody()->SetVelX(0);
	t->Restart();
	askEnd = false;
}

void SwordEnemyStandingState::exit() {
}

void SwordEnemyStandingState::update(const float dt_) {
	t->Update(dt_);

	if (t->Get() > 1) {
		askEnd = true;
	}
}

SwordEnemyStandingState::~SwordEnemyStandingState() {
	delete t;
}