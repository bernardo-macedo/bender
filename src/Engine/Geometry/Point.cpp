/*
 * Point.cpp
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#include "Point.h"

Point::~Point() {
	// TODO Auto-generated destructor stub
}

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

Point Point::operator +(Point other) {
	return Point(this->x + other.x, this->y + other.y);
}

void Point::operator +=(Point other) {
	this->x = this->x + other.x;
	this->y = this->y + other.y;
}

Point Point::operator -(Point other) {
	return Point(this->x - other.x, this->y - other.y);
}

void Point::operator -=(Point other) {
	this->x = this->x - other.x;
	this->y = this->y - other.y;
}

Point Point::operator *(float scalar) {
	return Point(this->x * scalar, this->y * scalar);
}

void Point::operator *=(float scalar) {
	this->x = this->x * scalar;
	this->y = this->y * scalar;
}

float Point::operator *(Point other) {
	return this->x * other.x + this->y * other.y;
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

float Point::distance(Point other) {
	float diffx = this->x - other.x;
	float diffy = this->y - other.y;
	return sqrt((diffx * diffx) + (diffy * diffy));
}
