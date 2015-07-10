/*
 * GameObject.cpp
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#include "GameObject.h"

const int GameObject::PEDRA_BASICO_BAON = 100;
const int GameObject::SPIKE_STONE_BAON = 101;
const int GameObject::PEDRA_BASICO_ENEMY = 102;
const int GameObject::BAON = 103;
const int GameObject::ENEMY = 104;
const int GameObject::PEDRA_BASICO_PULO_BAON = 105;
const int GameObject::SWORD_ENEMY = 106;
const int GameObject::TRANSPARENT_GAME_OBJECT = 107;

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

void GameObject::SetID(int i){
	this->id = i;
}

int GameObject::GetAngle(){
	return rotation;
}
