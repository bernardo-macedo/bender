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
	rotation = 0;
	SetPhysicalBody(false);
	red = 255;
	green = 255;
	blue = 255;
	alpha = 1;
}

Drawable::~Drawable() {
	// TODO Auto-generated destructor stub
}

float Drawable::getRotation() const {
	return rotation;
}

void Drawable::setRotation(float rotation) {
	this->rotation = rotation;
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
SDL_Texture* Drawable::GetTexture() {
	return texture;
}

void Drawable::SetTexture(SDL_Texture* texture) {
	this->texture = texture;
}
