/*
 * InputManager.cpp
 *
 *  Created on: 15/04/2015
 *      Author: Pedro
 */

#include "InputManager.h"

#include <iostream>

InputManager::InputManager():
	controllerHandler(new ControllerHandler())
{
	quitRequested = false;
	updateCounter = 0;
	for (int i = 0; i < 6; i++){
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}
}

InputManager::~InputManager() {
	// TODO Auto-generated destructor stub
	if(this->controllerHandler != nullptr){
		delete this->controllerHandler;
		this->controllerHandler = nullptr;
	}
}

void InputManager::Update() {
	SDL_Event event;

	updateCounter++;
	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		this->controllerHandler->handleInput(event);

		for(unsigned int i = 0; i < this->controllStates.size(); i++)
			if(this->controllerHandler->controllStates[i]){
				keyState[SDLK_UP] = true;
				keyUpdate[SDLK_UP] = updateCounter;
		}

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
			break;

			case SDL_MOUSEBUTTONUP:
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
			break;

			case SDL_KEYUP:
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			break;

			case SDL_KEYDOWN:
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			break;
		}
	}
}

bool InputManager::KeyPress(int key) {
	if(updateCounter == keyUpdate[key] && keyState[key]){
		return true;
	}
	return false;
}

bool InputManager::KeyRelease(int key) {
	if(updateCounter == keyUpdate[key] && !keyState[key]){
		return true;
	}
	return false;
}

bool InputManager::IsKeyDown(int key) {
	return keyState[key];
}

bool InputManager::MousePress(int button) {
	if(updateCounter == mouseUpdate[button] && mouseState[button]){
		return true;
	}
	return false;
}

void InputManager::SetKeyPressed(SDL_Keycode key){
	keyState[key] = true;
	keyUpdate[key] = updateCounter;
}

void InputManager::SetKeyReleased(SDL_Keycode key){
	keyState[key] = false;
	keyUpdate[key] = updateCounter;
}

bool InputManager::MouseRelease(int button) {
	if(updateCounter == mouseUpdate[button] && !mouseState[button]){
		return true;
	}
	return false;
}

bool InputManager::IsMouseDown(int button) {
	return mouseState[button];
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}

bool InputManager::QuitRequested() {
	return quitRequested;
}

InputManager& InputManager::GetInstance() {
	static InputManager inputManager;
	return inputManager;
}
