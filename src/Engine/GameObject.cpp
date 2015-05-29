/*
 * GameObject.cpp
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#include "GameObject.h"

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
}

Rect GameObject::GetBox(){
	return box;
}

void GameObject::SetPos(int x, int y) {
	box.SetX(x);
	box.SetY(y);
}

void GameObject::SetPosX(int x) {
	box.SetX(x);
}

void GameObject::SetPosY(int y) {
	box.SetY(y);
}

int GameObject::GetID() {
	return id;
}

int GameObject::GetAngle(){
	return rotation;
}
