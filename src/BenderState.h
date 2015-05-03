/*
 * BenderState.h
 *
 *  Created on: 30/04/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_BENDERSTATE_H_
#define ENGINE_BENDERSTATE_H_

#include "Engine/TileSet/TileSet.h"
#include "Engine/TileSet/TileMap.h"
#include "Engine/Sprite.h"
#include "Engine/State.h"

class BenderState : public State{
private:
	TileSet *tileSet;
	TileMap *tileMap;
	Sprite* bg;
	Minion* m;
public:
	virtual ~BenderState();

	void Setup();
	void Update();
	void Render();
};

#endif /* ENGINE_BENDERSTATE_H_ */
