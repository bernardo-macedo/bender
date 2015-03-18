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

std::list<Force*> Body::GetForces() {
	return forces;
}

void Body::ApplyForce(Force* f) {
	forces.push_back(f);
}

void Body::SetAngularVel(float vel) {
	this->angularVel = vel;
}

float Body::GetAngularVel() {
	return angularVel;
}

void Body::SetAngularAccel(float accel) {
	this->angularAccel = accel;
}

float Body::GetAngularAccel() {
	return angularAccel;
}

void Body::removeForce(std::string id) {
	for(std::list<Force*>::iterator i = forces.begin(); i != forces.end(); i++){
		Force* f = (Force*)*i;
		if(f->GetId().compare(id) == 0){
			forces.remove(f);
			break;
		}
	}
}
