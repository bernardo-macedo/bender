/*
 * Enemy.h
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include <map>
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Physics/Body.h"
#include "Engine/Timer.h"
#include "StateEnemy.h"
#include "Being.h"

#define ENEMY_MAP_GROUND 430

class StateEnemy;

class Enemy : public Being {
public:
	enum enemyStates {STAND, WALK, JUMP, RUN, FALLING, PATROLLING, FOLLOW, PUNCH};
	enum runController {NONE, PRERUNR, PRERUNL};
	Enemy(int enemyScale);
	virtual ~Enemy();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision();
	bool IsDead();
	bool Is(std::string type);

	Sprite* GetSprite();

	void Run(bool flipped);
	void Walk(bool flipped);
	void Stand(bool flipped);
	void Jump(bool flipped);

	void changeState(const enemyStates state_);
	bool IsState(const enemyStates state_);
	bool StateEnd();

	Timer* Time();

	void SetDead(bool isDead_);

private:
	int WALK_SPEED_E;
	int RUN_SPEED_E;
	float DOUBLECLICK_TIME;

	Sprite *sp;
	StateEnemy* currentState;
	std::map<enemyStates, StateEnemy*> enemyStatesMap;
	runController runStates;
	std::vector<int> spriteData;
	int numEst;
	bool flipped;
	Timer *t;
	bool isDead;
	int fallUpdateCount;
	void InitializeStates();

};

#endif /* ENEMY_H_ */
