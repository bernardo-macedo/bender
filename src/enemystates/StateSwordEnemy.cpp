/*
 * StateSwordEnemy.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: -Bernardo
 */

#include "StateSwordEnemy.h"

StateSwordEnemy::StateSwordEnemy(SwordEnemy* const enemy_) :
	enemy(enemy_), askEnd(false) {

}

StateSwordEnemy::~StateSwordEnemy() {
	this->enemy = nullptr;
}

bool StateSwordEnemy::AskEnd() {
	return askEnd;
}
