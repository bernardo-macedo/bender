/*
 * Force.cpp
 *
 *  Created on: 15/03/2015
 *      Author: Pedro
 */

#include "Force.h"

Force::Force(std::string id, float x, float y) {
	this->x = x;
	this->y = y;
	this->id = id;
}

Force::~Force() {
	// TODO Auto-generated destructor stub
}

float Force::GetX() {
	return x;
}

float Force::GetY() {
	return y;
}

void Force::SetX(float x) {
	this->x = x;
}

void Force::SetY(float y) {
	this->y = y;
}

std::string Force::GetId() {
	return id;
}
