/*
 * StateThree.h
 *
 *  Created on: Jul 4, 2015
 *      Author: -Bernardo
 */

#ifndef STAGETHREE_H_
#define STAGETHREE_H_

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
#include "EnemyAIManager.h"

class StageThree : public AbstractStage {
public:
	StageThree(int posX = -1);
	virtual ~StageThree();

	bool OnLevelWon(float dt);

};

#endif /* STAGETHREE_H_ */
