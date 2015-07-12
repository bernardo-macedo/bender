/*
 * Point.cpp
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#include <math.h>
#include "Point.h"

Point::~Point() {
	// TODO Auto-generated destructor stub
}

Point::Point(float x, float y){
	this->x = x;
	this->y= y;
}

Point::Point(){
	x = 0;
	y = 0;
}
float Point::getX() {
	return x;
}

void Point::setX(float x) {
	this->x = x;
}

float Point::getY() {
	return y;
}

void Point::setY(float y) {
	this->y = y;
}

float Point::Distance(Point other) {
	float diffx = this->x - other.getX();
	float diffy = this->y - other.getY();
	return sqrt((diffx * diffx) + (diffy * diffy));
}
