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
#include "TileSet/TileSet.h"
#include "TileSet/TileMap.h"
#include "Resources.h"

class State {
private:
	Sprite* bg;
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;
	TileSet *tileSet;
	TileMap *tileMap;
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
