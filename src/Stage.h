/*
 * Stage.h
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#ifndef STAGE_H_
#define STAGE_H_

#include <memory>
#include "Engine/State.h"
#include "Engine/TileSet/TileMap.h"
#include "Engine/Game.h"
#include "Engine/Timer.h"
#include "Baon.h"
#include "Enemy.h"
#include "Monumento.h"
#include "EnemyAIManager.h" 
#include "Being.h"
#include "Engine/Music.h"
#include "Scroll.h"
#include "Hud.h"
#include "StageTwo.h"

class Stage : public State{
public:
	Stage();
	virtual ~Stage();

	void Update(float dt);
	void Render();

	void Pause() ;
	void Resume();
	Baon* GetPlayer();
	void CollisionEnemies(int i);
private:
	Baon* baon;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Monumento>> monuments;
	Sprite *sp;
	TileMap* tileMap;
	EnemyAIManager *enemyAI;
	Music *music;
	Timer* levelUpTimer;
};

#endif /* STAGE_H_ */
