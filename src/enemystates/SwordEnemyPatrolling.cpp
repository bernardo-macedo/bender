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
}

void SwordEnemyPatrolling::exit() {
}

void SwordEnemyPatrolling::update(const float dt_) {
}
