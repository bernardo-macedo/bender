/*
 * Camera.cpp
 *
 *  Created on: 16/04/2015
 *      Author: Pedro
 */

#include "Camera.h"

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = NULL;
}

void Camera::Update(float dt) {
	((void) dt);
	if(focus != NULL){
		pos.setX(focus->GetBox().GetX());
		pos.setY(focus->GetBox().GetY());
	}
}
