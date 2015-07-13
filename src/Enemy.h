/*
 * Enemy.h
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "AbstractEnemy.h"
#include "Engine/Sound.h"

class StateEnemy;

class Enemy : public AbstractEnemy {
public:
	enum enemyStates {STAND, WALK, JUMP, RUN, FALLING, PATROLLING, FOLLOW, PUNCH, BEND, TAKINGHIT, DYING, BEINGPUSHED};

	Enemy(int enemyScale, int x);
	virtual ~Enemy();

	void changeState(const enemyStates state_);
	bool IsState(const enemyStates state_);
	bool StateEnd();

	void Update(float dt);

	void NotifyCollision(GameObject* other);
	void NotifyTileCollision(Collision::CollisionAxis collisionAxis);
	bool Is(std::string type);

	float GetCoolDown();
	void SetCoolDown(float coolDown);

private:
	float bendCoolDown;
	StateEnemy* currentState;
	std::map<enemyStates, StateEnemy*> enemyStatesMap;

	void InitializeStates();
	void InitializeSprite();
	void InitializeForces();
	void Initialize();

	void SetWalkSprite();
	void SetStandSprite();
	void SetJumpSprite();
	void SetTakingDamageSprite();
	void SetDyingSprite();
	void SetAttackingSprite();

};

#endif /* ENEMY_H_ */
