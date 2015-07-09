/*
 * AbstractStage.h
 *
 *  Created on: Jul 4, 2015
 *      Author: -Bernardo
 */

#ifndef ABSTRACTSTAGE_H_
#define ABSTRACTSTAGE_H_

#include <stddef.h>
#include "Engine/State.h"
#include "Engine/TileSet/TileMap.h"
#include "Engine/Music.h"
#include "Engine/InputManager.h"
#include "Engine/Camera.h"
#include "Engine/Text.h"
#include "Engine/Collision.h"
#include "Engine/Game.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Timer.h"
#include "Engine/Sound.h"
#include "Baon.h"
#include "PedraBasico.h"
#include "Scroll.h"
#include "Hud.h"
#include "Monumento.h"
#include "AbstractEnemy.h"
#include "EnemyAIManager.h"
#include "SwordEnemyAIManager.h"

class AbstractStage : public State {
public:
	AbstractStage(int scale, int level, int posX = -1);
	virtual ~AbstractStage();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

	virtual bool OnLevelWon(float dt) = 0;

protected:
	Baon* baon;
	Music *music;
	Sound *levelWonSound;
	Timer* levelUpTimer;
	Text* levelUpText;
	int scale;
	int level;
	bool levelWon;

	std::vector<std::unique_ptr<AbstractEnemy>> enemies;
	std::vector<std::unique_ptr<Monumento>> monuments;
	EnemyAIManager *enemyAI;
	SwordEnemyAIManager *swordEnemyAI;
};

#endif /* ABSTRACTSTAGE_H_ */
