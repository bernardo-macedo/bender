/*
 * Body.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "Body.h"

using namespace std;

Body::~Body() {
	// TODO Auto-generated destructor stub
}

float Body::getAccelX() const {
	return accelX;
}

void Body::setAccelX(float accelX) {
	this->accelX = accelX;
}

float Body::getAccelY() const {
	return accelY;
}

void Body::setAccelY(float accelY) {
	this->accelY = accelY;
}

float Body::getVelX() const {
	return velX;
}

void Body::setVelX(float velX) {
	this->velX = velX;
}

float Body::getVelY() const {
	return velY;
}

void Body::setVelY(float velY) {
	this->velY = velY;
}

