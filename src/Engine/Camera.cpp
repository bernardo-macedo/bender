/*
 * Camera.cpp
 *
 *  Created on: 16/04/2015
 *      Author: Pedro
 */

#include "Camera.h"
#include <math.h>
#include <iostream>

GameObject* Camera::focus = NULL;
Point Camera::speed;
Point Camera::pos;

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = NULL;
}

void Camera::Update(float dt) {
	if (focus != NULL) {
		// centraliza foco na tela
		pos.setX(focus->GetBox().GetX() - (Constants::WindowWidth / 2));
		pos.setY(focus->GetBox().GetY() - (Constants::WindowHeight / 2));
	} else {
		// responde de acordo com dt e o input
		speed = 400 * dt;

		bool down = InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY);
		bool up = InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY);
		bool left = InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY);
		bool right = InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY);

		float verticalMovement = (left || right) ? sin(45 * M_PI / 180) * speed.getY() : speed.getY();
		float horizontalMovement = (up || down) ? cos(45 * M_PI / 180) * speed.getX() : speed.getX();

		if (down) {
			pos.setY(pos.getY() - verticalMovement);
		}

		if (up) {
			pos.setY(pos.getY() + verticalMovement);
		}

		if (left) {
			pos.setX(pos.getX() + horizontalMovement);
		}

		if (right) {
			pos.setX(pos.getX() - horizontalMovement);
		}


	}
}
