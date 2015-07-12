/*
 * BenderEnemyStateStanding.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#include "BenderEnemyStateStanding.h"


void BenderEnemyStateStanding::enter() {
	enemy->GetSprite()->SetFrameWidth(38);
	enemy->GetSprite()->SetFrameHeight(50);
	enemy->GetSprite()->SetFrameCount(2);
	enemy->GetSprite()->SetLine(0, 60);
	enemy->GetBody()->SetVelX(0);
	t->Restart();
	askEnd = false;
}

void BenderEnemyStateStanding::exit() {
}

BenderEnemyStateStanding::~BenderEnemyStateStanding() {
	delete t;
}

void BenderEnemyStateStanding::update(const float dt_) {
	t->Update(dt_);

	if (t->Get() > 1) {
		askEnd = true;
	}
}
