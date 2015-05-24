/*
 * State.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_STAGESTATE_H_
#define ENGINE_STAGESTATE_H_

#include <iostream>
#include <vector>
#include <memory>

#include "SDL.h"
#include "Sprite.h"
#include "../Alien.h"
#include "../Penguins.h"
#include "TileSet/TileSet.h"
#include "TileSet/TileMap.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"
#include "State.h"
#include "Music.h"
#include "Text.h"

class StageState : public State{
private:
	Sprite* bg;
	TileSet *tileSet;
	TileMap *tileMap;
	Camera *camera;
	Alien* a;
	Penguins *p;
	Music* music;
	int alienCount, initialAlienCount;
public:
	StageState();
	virtual ~StageState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
};

#endif /* ENGINE_STAGESTATE_H_ */
