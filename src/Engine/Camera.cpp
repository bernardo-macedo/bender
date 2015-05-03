/*
 * Camera.cpp
 *
 *  Created on: 16/04/2015
 *      Author: Pedro
 */

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Point Camera::pos;
GameObject* Camera::focus = NULL;

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = NULL;
}

void Camera::Update(float dt) {
	if(focus != NULL){
		pos.setX(focus->GetBox().GetX() - Game::SCREEN_WIDTH/2);
		pos.setY(focus->GetBox().GetY() - Game::SCREEN_HEIGHT/2);
	}
}
