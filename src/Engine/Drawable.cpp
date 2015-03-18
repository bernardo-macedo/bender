/*
 * Drawable.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "Drawable.h"

using namespace std;
Drawable::Drawable(string id, float x, float y) {
	this->id = id;
	this->x = x;
	this->y = y;
	rotationX = 0;
	rotationY = 0;
	SetPhysicalBody(false);
	red = 255;
	green = 255;
	blue = 255;
	alpha = 1;
}

Drawable::~Drawable() {
	// TODO Auto-generated destructor stub
}

float Drawable::getRotationX() const {
	return rotationX;
}

void Drawable::setRotationX(float rotationX) {
	this->rotationX = rotationX;
}

float Drawable::getRotationY() const {
	return rotationY;
}

void Drawable::setRotationY(float rotationY) {
	this->rotationY = rotationY;
}

float Drawable::getX() const {
	return x;
}

void Drawable::setX(float x) {
	this->x = x;
}

float Drawable::getY() const {
	return y;
}

void Drawable::setY(float y) {
	this->y = y;
}

void Drawable::setID(std::string id) {
	this->id = id;
}

void Drawable::SetPhysicalBody(bool isBody) {
	this->phisicalBody = true;
}

bool Drawable::IsPhysicalBody() {
	return this->phisicalBody;
}

string Drawable::getID() const {
	return id;
}

void Drawable::Render(){
	OnRender();
}

void Drawable::SetColor(int r, int g, int b, int a) {
	red = r;
	green = g;
	blue = b;
	alpha = a;
}
