/*
 * TransparentGameObject.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#include "TransparentGameObject.h"

#include <string>

TransparentGameObject::TransparentGameObject(int x, int y, int w, int h, bool right) {
	SetID(GameObject::TRANSPARENT_GAME_OBJECT);
	this->right = right;

	box.SetX(x);
	box.SetY(y);
	box.SetW(w);
	box.SetH(h);
	dead = false;
}

void TransparentGameObject::Update(float dt) {
}

bool TransparentGameObject::IsDead() {
	return dead;
}

void TransparentGameObject::Render() {
}

void TransparentGameObject::NotifyCollision(GameObject* other) {
}

bool TransparentGameObject::Is(std::string type) {
	return false;
}

void TransparentGameObject::SetDead(bool dead) {
	this->dead = dead;
}

bool TransparentGameObject::IsRight() {
	return right;
}
