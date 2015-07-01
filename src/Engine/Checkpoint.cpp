/*
 * Checkpoint.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: -Bernardo
 */

#include "Checkpoint.h"

Checkpoint::Checkpoint(unsigned int level, int posX) {
	this->level = level;
	this->posX = posX;
}

Checkpoint::~Checkpoint() {}

unsigned int Checkpoint::GetLevel() {
	return level;
}

int Checkpoint::GetPositionX() {
	return posX;
}
