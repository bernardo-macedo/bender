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
#include "Baon.h"
#include "Enemy.h"
#include "Monumento.h"
#include "EnemyAIManager.h" 
#include "Being.h"
#include "Engine/Music.h"

class Stage : public State{
public:
	Stage();
	virtual ~Stage();

	void Update(float dt);
	void Render();

	void Pause() ;
	void Resume();
	Baon* GetPlayer();
private:
	Baon* baon;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Monumento>> monuments;
	Sprite *sp;
	TileMap* tileMap;
	EnemyAIManager *enemyAI;
	Music *music;
};

#endif /* STAGE_H_ */
