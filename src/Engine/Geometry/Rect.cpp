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
