/*
 * BigEnemyStateFollow.cpp
 *
 *  Created on: Jul 12, 2015
 *      Author: -Bernardo
 */

#include "BigEnemyStateFollow.h"

BigEnemyStateFollow::BigEnemyStateFollow(BigEnemy* const enemy_) : StateBigEnemy(enemy_) {}

void BigEnemyStateFollow::enter() {
	askEnd = false;
	enemy->SetWalkSprite();
}

void BigEnemyStateFollow::exit() {
}

void BigEnemyStateFollow::update(const float dt_) {
	bool flipped = false;
	if ((abs(enemy->GetDistanceToBaon()) > 30 * enemy->GetScale() || abs(enemy->GetDistanceToBaon()) < 150 * enemy->GetScale())) {

		flipped = (enemy->GetDistanceToBaon() > 0);
		enemy->Run(flipped);
		enemy->GetSprite()->Update(dt_);

	} else {
		askEnd = true;
	}
}
