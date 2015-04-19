/*
 * State.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_STATE_H_
#define ENGINE_STATE_H_

#include <iostream>
#include <vector>
#include <memory>

#include "Sprite.h"
#include "Face.h"
#include "TileSet/TileSet.h"
#include "TileSet/TileMap.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"

#ifdef __linux__

#include <SDL2/SDL.h>

#elif _WIN32

#include "SDL.h"

#else     
#error Platform not supported

#endif

class State {
private:
	Sprite* bg;
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;
	TileSet *tileSet;
	TileMap *tileMap;
	Camera *camera;
public:
	State();
	virtual ~State();

	void Input();
	void AddObject(float mouseX, float mouseY);
	bool QuitRequested();
	void Update();
	void Render();
};

#endif /* ENGINE_STATE_H_ */
