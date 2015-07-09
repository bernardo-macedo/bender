/*
 * SwordEnemyAIManager.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef SWORDENEMYAIMANAGER_H_
#define SWORDENEMYAIMANAGER_H_

#include "Baon.h"
#include "SwordEnemy.h"
#include "Engine/Collision.h"

class SwordEnemyAIManager {
public:
	SwordEnemyAIManager(Baon* baon_, SwordEnemy* enemy_);
	~SwordEnemyAIManager();
	void update(const float dt);

	void SetEnemy(SwordEnemy* enemy);

private:

	SwordEnemy* enemy;
	Baon* baon;
};

#endif /* SWORDENEMYAIMANAGER_H_ */
