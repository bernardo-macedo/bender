/*
 * StateBigEnemy.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: -Bernardo
 */

#include "StateBigEnemy.h"

StateBigEnemy::StateBigEnemy(BigEnemy* const enemy_) : enemy(enemy_) {
	askEnd = false;
}

StateBigEnemy::~StateBigEnemy() {
	enemy = nullptr;
}

bool StateBigEnemy::AskEnd() {
	return askEnd;
}
