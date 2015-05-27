/*
 * Stage.h
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#ifndef STAGE_H_
#define STAGE_H_

#include "Engine/State.h"
#include "Engine/TileSet/TileMap.h"
#include "Engine/Game.h"
#include "Baon.h"

class Stage : public State{
public:
	Stage();

	void Update(float dt);
	void Render();

	void Pause() ;
	void Resume();
	Baon* GetPlayer();
private:
	Baon* baon;
	Sprite *sp;
	TileMap* tileMap;
};

#endif /* STAGE_H_ */
