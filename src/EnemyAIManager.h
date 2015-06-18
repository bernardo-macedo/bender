#ifndef INCLUDE_ENEMYAIMANAGER_H
#define INCLUDE_ENEMYAIMANAGER_H

#include "Enemy.h"
#include "Baon.h"

class EnemyAIManager{

	public:

		EnemyAIManager(Baon* baon_, Enemy* enemy_);
		~EnemyAIManager();
		void update(const float dt);

		void SetEnemy(Enemy* enemy);

	private:

		Enemy* enemy;
		Baon* baon;
};

#endif /* INCLUDE_ENEMYAIMANAGER_H */
