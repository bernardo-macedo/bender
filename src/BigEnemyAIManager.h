/*
 * BigEnemyAIManager.h
 *
 *  Created on: Jul 12, 2015
 *      Author: -Bernardo
 */

#ifndef BIGENEMYAIMANAGER_H_
#define BIGENEMYAIMANAGER_H_

#include "Baon.h"
#include "BigEnemy.h"
#include "Engine/Collision.h"

class BigEnemyAIManager {
public:
	BigEnemyAIManager(Baon* baon_, BigEnemy* enemy_);
	virtual ~BigEnemyAIManager();
	void update(const float dt);

	void SetEnemy(BigEnemy* enemy);

private:

	BigEnemy* enemy;
	Baon* baon;
};

#endif /* BIGENEMYAIMANAGER_H_ */
