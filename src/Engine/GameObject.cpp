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
