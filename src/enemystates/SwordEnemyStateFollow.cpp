/*
 * SwordEnemyStateFollow.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyStateFollow.h"

SwordEnemyStateFollow::SwordEnemyStateFollow(SwordEnemy* const enemy_) : StateSwordEnemy(enemy_) {}

void SwordEnemyStateFollow::enter() {
	askEnd = false;
	enemy->SetWalkSprite();
}

void SwordEnemyStateFollow::exit() {}

void SwordEnemyStateFollow::update(const float dt_) {
	bool flipped = false;
	if ((abs(enemy->GetDistanceToBaon()) > 30 * enemy->GetScale() || abs(enemy->GetDistanceToBaon()) < 150 * enemy->GetScale())) {

		flipped = (enemy->GetDistanceToBaon() > 0);
		enemy->Run(flipped);
		enemy->GetSprite()->Update(dt_);

	} else {
		askEnd = true;
	}
}
