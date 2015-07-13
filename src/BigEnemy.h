/*
 * BigEnemy.h
 *
 *  Created on: Jul 11, 2015
 *      Author: -Bernardo
 */

#ifndef BIGENEMY_H_
#define BIGENEMY_H_

#include "AbstractEnemy.h"
#include "Engine/Sound.h"

class StateBigEnemy;

class BigEnemy : public AbstractEnemy {

public:
	enum enemyStates {STAND, WALK, ATTACK, TAKINGHIT, DYING, PATROLLING, FOLLOW, BEINGPUSHED};

	BigEnemy(int enemyScale, int x);
	virtual ~BigEnemy();

	void changeState(const enemyStates state_);
	bool IsState(const enemyStates state_);
	bool StateEnd();

	void Update(float dt);

	void NotifyCollision(GameObject* other);
	void NotifyTileCollision(Collision::CollisionAxis collisionAxis);
	bool Is(std::string type);

	void SetWalkSprite();
	void SetStandSprite();
	void SetJumpSprite();
	void SetTakingDamageSprite();
	void SetDyingSprite();
	void SetAttackingSprite();
	void SetDistanceToBaon(float distance);
	float GetDistanceToBaon();
	bool HasCollidedHorizontally();

private:
	StateBigEnemy* currentState;
	std::map<enemyStates, StateBigEnemy*> enemyStatesMap;
	float distanceToBaon;
	bool collidedHorizontally;

	void InitializeStates();
	void InitializeSprite();
	void InitializeForces();
	void Initialize();
};

#endif /* BIGENEMY_H_ */
