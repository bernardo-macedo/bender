/*
 * Enemy.h
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Physics/Body.h"
#include "Engine/Timer.h"
#include "StateEnemy.h"
#include <map>
#define MAP_GROUND 500

class StateEnemy;

class Enemy : public GameObject {
public:
	enum enemyStates {STAND, WALK, JUMP, RUN, FALLING, PATROLLING, FOLLOW};
	enum runController {NONE, PRERUNR, PRERUNL};
	Enemy();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	bool IsDead();
	bool Is(std::string type);

	Sprite* getSprite();

	void Run(bool flipped);
	void Walk(bool flipped);
	void Stand(bool flipped);
	void Jump(bool flipped);

	void changeState(const enemyStates state_);

	Timer* Time();
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
	Body *b;
	Timer *t;
	int fallUpdateCount;
	void InitializeStates();

};

#endif /* ENEMY_H_ */
