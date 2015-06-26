/*
 * SwordEnemyPatrolling.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyPatrolling.h"



SwordEnemyPatrolling::SwordEnemyPatrolling(SwordEnemy* const enemy_) :
	StateSwordEnemy(enemy_), isLeft(false) {
}

SwordEnemyPatrolling::~SwordEnemyPatrolling() {
	// TODO Auto-generated destructor stub
}

void SwordEnemyPatrolling::enter() {
	enemy->GetSprite()->SetFrameWidth(50);
	enemy->GetSprite()->SetFrameHeight(50);
	enemy->GetSprite()->SetFrameCount(6);
	enemy->GetSprite()->SetLine(1, 50);
}

void SwordEnemyPatrolling::exit() {
}

void SwordEnemyPatrolling::update(const float dt_) {
	enemy->GetSprite()->Update(dt_);
}
