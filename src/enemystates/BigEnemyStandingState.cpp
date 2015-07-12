/*
 * BigEnemyStandingState.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#include "BigEnemyStandingState.h"

void BigEnemyStandingState::enter() {
	enemy->GetSprite()->SetFrameWidth(38);
	enemy->GetSprite()->SetFrameHeight(60);
	enemy->GetSprite()->SetFrameCount(2);
	enemy->GetSprite()->SetLine(0, 60);
	enemy->GetBody()->SetVelX(0);
	t->Restart();
	askEnd = false;
}

void BigEnemyStandingState::exit() {
}

void BigEnemyStandingState::update(const float dt_) {
	t->Update(dt_);

	if (t->Get() > 1) {
		askEnd = true;
	}
}

BigEnemyStandingState::~BigEnemyStandingState() {
	delete t;
}
