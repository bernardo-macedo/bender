/*
 * InputManager.h
 *
 *  Created on: 15/04/2015
 *      Author: Pedro
 */

#ifndef ENGINE_INPUTMANAGER_H_
#define ENGINE_INPUTMANAGER_H_

#include <unordered_map>
#include <iostream>
#include "ControllerHandler.h"

#ifdef __linux__

#include <SDL2/SDL.h>

#elif _WIN32

#include "SDL.h"

#else     
#error Platform not supported

#endif

class InputManager {
private:
	bool mouseState[6];
	int mouseUpdate[6];

	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

	ControllerHandler* controllerHandler; /**< Handles input if joystick is present. */
	std::array<bool, 6> controllStates; /**< Boolean array that controls which keys are
		pressed or not. */

	bool quitRequested;
	int updateCounter;

	int mouseX, mouseY;

	InputManager();
	virtual ~InputManager();
public:
	void Update();

	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	void SetKeyPressed(SDL_Keycode key);

	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	void SetKeyReleased(SDL_Keycode key);

	int GetMouseX();
	int GetMouseY();

	bool QuitRequested();

	static InputManager& GetInstance();
};

#endif /* ENGINE_INPUTMANAGER_H_ */
