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

#include "SDL.h"
#include "Sprite.h"
#include "../Face.h"
#include "../Minion.h"
#include "TileSet/TileSet.h"
#include "TileSet/TileMap.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"

class State {
protected:
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;
public:
	State();
	virtual ~State();

	void AddObject(GameObject* object);
	bool QuitRequested();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Setup() = 0;
};

#endif /* ENGINE_STATE_H_ */
