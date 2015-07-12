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
#include "Engine/Text.h"
#include "Baon.h"
#include "Enemy.h"
#include "SwordEnemy.h"
#include "BigEnemy.h"
#include "Monumento.h"
#include "EnemyAIManager.h" 
#include "Being.h"
#include "Engine/Music.h"
#include "Scroll.h"
#include "Hud.h"
#include "StageTwo.h"
#include "AbstractStage.h"

class Stage : public AbstractStage {
public:
	Stage(int posX = -1);
	virtual ~Stage();

	bool OnLevelWon(float dt);
};

#endif /* STAGE_H_ */
