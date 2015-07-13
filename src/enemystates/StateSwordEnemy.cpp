/*
 * StateSwordEnemy.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "StateSwordEnemy.h"

StateSwordEnemy::StateSwordEnemy(SwordEnemy* const enemy_)  : enemy(enemy_) {
	askEnd = false;
}

StateSwordEnemy::~StateSwordEnemy() {
	this->enemy = nullptr;
}

bool StateSwordEnemy::AskEnd() {
	return askEnd;
}
