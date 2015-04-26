/*
 * Rect.cpp
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#include "Rect.h"

float Rect::GetX() {
	return x;
}

void Rect::SetX(float x) {
	this->x = x;
}

float Rect::GetY() {
	return y;
}

void Rect::SetY(float y) {
	this->y = y;
}

Rect::~Rect() {
	// TODO Auto-generated destructor stub
}

float Rect::GetW() {
	return w;
}

void Rect::SetW(float w) {
	this->w = w;
}

float Rect::GetH() {
	return h;
}

void Rect::SetH(float h) {
	this->h = h;
}

bool Rect::IsInside(float x, float y) {
	if(x < this->x + this->w && x > this->x
			&& y > this->y && y < this->y + this->h){
		return true;
	}

	return false;
}

bool Rect::CollidesWith(Rect other) {
	float diffX = (this->x - this->w / 2)
			- (other.x - other.w / 2);
	float diffY = (this->y - this->h / 2)
			- (other.y - other.h / 2);

	if (diffX > other.w || -diffX > this->w) {
		return false;
	}
	if (diffY > other.h || -diffY > this->h) {
		return false;
	}

	return true;

}

Point Rect::Intersection(Rect other) {
	float minDistanceX = this->w / 2 + other.w / 2;
	float minDistanceY = this->h / 2 + other.h / 2;

	float distanceX = this->x - other.x;
	float distanceY = this->y - other.y;

	if (fabs(distanceX) > minDistanceX || fabs(distanceY) > minDistanceY) {
		Point p;
		return p;
	}

	distanceX = distanceX > 0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
	distanceY = distanceY > 0 ? minDistanceY - distanceY : -minDistanceY - distanceY;

	Point p(distanceX, distanceY);
	return p;
}
