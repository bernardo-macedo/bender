/*
 * Camera.cpp
 *
 *  Created on: 16/04/2015
 *      Author: Pedro
 */

#include "Camera.h"

#include "SDL_Wrapper.h"

#include "Game.h"
#include "InputManager.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

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
		float newPos = -focus->GetBox().GetX() + 3 * Game::SCREEN_WIDTH/8;
		if (newPos < 0) {
			pos.setX(newPos);
		}
	}
}
