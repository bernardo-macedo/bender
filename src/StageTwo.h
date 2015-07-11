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
#include "Engine/Text.h"
#include "AbstractStage.h"
#include "Scroll.h"
#include "Hud.h"
#include "Monumento.h"
#include "Enemy.h"
#include "SwordEnemy.h"
#include "EnemyAIManager.h"
#include "SwordEnemyAIManager.h"
#include "StageThree.h"

class StageTwo : public AbstractStage {
public:
	StageTwo(int posX = -1);
	virtual ~StageTwo();

	bool OnLevelWon(float dt);

};

#endif /* STAGETWO_H_ */
