/*
 * SwordEnemy.h
 *
 *  Created on: Jun 26, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_SWORDENEMY_H_
#define ENEMYSTATES_SWORDENEMY_H_

#include <map>
#include <string>
#include <vector>

#include "../Being.h"
#include "../Engine/Sprite.h"
#include "../Engine/Timer.h"
#include "../Engine/Physics/Physic.h"
#include "../Engine/Camera.h"

class StateSwordEnemy;

#define ENEMY_MAP_GROUND 143

class SwordEnemy : public Being {
public:
	enum enemyStates {STAND, WALK, ATTACK, TAKEDAMAGE, DYING, PATROLLING, FOLLOW};

	SwordEnemy(int enemyScale, int x);
	virtual ~SwordEnemy();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision();
	bool IsDead();
	bool Is(std::string type);
	bool GetFlipped();

	void ChangeState(const enemyStates state_);
	bool IsState(const enemyStates state_);
	bool StateEnd();

	void Stand();
	void Walk();
	void Attack();
	void TakeDamage();
	void Die();

	bool IsDead();
	bool IsRemovable();

private:
	Sprite* sp;
	Timer* t;

	StateSwordEnemy* currentState;
	std::map<enemyStates, StateSwordEnemy*> enemyStatesMap;

	std::vector<int> spriteData;
	int numEst;

	int scale;
	int hp;
	int WALK_SPEED_E;

	bool flipped;
	bool isDead;
	bool isRemovable;

	void LoadSpriteData();
	void InitializeStates();
};

#endif /* ENEMYSTATES_SWORDENEMY_H_ */
