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

float Body::GetAccelX(){
	return accelX;
}

void Body::SetAccelX(float accelX) {
	this->accelX = accelX;
}

float Body::GetAccelY(){
	return accelY;
}

void Body::SetAccelY(float accelY) {
	this->accelY = accelY;
}

float Body::GetVelX(){
	return velX;
}

void Body::SetVelX(float velX) {
	this->velX = velX;
}

float Body::GetVelY(){
	return velY;
}

void Body::SetVelY(float velY) {
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

float Body::GetRotation() {
	return rotation;
}

void Body::SetRotation(float r) {
	rotation = r;
}

void Body::SetX(float x) {
	this->x = x;
}

void Body::SetY(float y) {
	this->y = y;
}

float Body::GetX() {
	return x;
}

float Body::GetY() {
	return y;
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

float Body::GetResistance() {
	return resistance;
}

void Body::SetResistance(float r) {
	resistance = r;
}

Force* Body::GetForce(std::string id){
	for(std::list<Force*>::iterator i = forces.begin(); i != forces.end(); i++){
		Force* f = (Force*)*i;
		if(f->GetId().compare(id) == 0){
			return f;
		}
	}
	return NULL;
}

void Body::SetSpeedLimit(float sl) {
	this->speedLimit = sl;
}

float Body::GetSpeedLimit() {
	return speedLimit;
}
