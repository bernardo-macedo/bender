/*
 * StageTwo.h
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#ifndef STAGETWO_H_
#define STAGETWO_H_

#include "Engine/State.h"
#include "Engine/TileSet/TileMap.h"
#include "Engine/Music.h"
#include "Engine/InputManager.h"
#include "Engine/Camera.h"
#include "Scroll.h"
#include "Hud.h"

class StageTwo : public State {
public:
	StageTwo();
	virtual ~StageTwo();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Baon* baon;
	TileMap* tileMap;
	Music *music;
};

#endif /* STAGETWO_H_ */
