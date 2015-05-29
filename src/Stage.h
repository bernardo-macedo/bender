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
#include "Enemy.h"
#include "Monumento.h"
#include "EnemyAIManager.h" 

class Stage : public State{
public:
	Stage();

	void Update(float dt);
	void Render();

	void Pause() ;
	void Resume();
	Baon* GetPlayer();
	void ResolveCollision(Body previousBody, float dt, bool vertical);
private:
	Baon* baon;
	std::vector<Enemy*> enemies;
	std::vector<Monumento*> monuments;
	Sprite *sp;
	TileMap* tileMap;
	EnemyAIManager *enemyAI;
};

#endif /* STAGE_H_ */
