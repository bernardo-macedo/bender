/*
 * SwordEnemy.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef SWORDENEMY_H_
#define SWORDENEMY_H_

#include <map>
#include <string>
#include "Engine/Sound.h"
#include "AbstractEnemy.h"

class StateSwordEnemy;

class SwordEnemy : public AbstractEnemy {
public:
	enum enemyStates {STAND, WALK, ATTACK, TAKINGHIT, DYING, PATROLLING, FOLLOW, BEINGPUSHED};

	SwordEnemy(int enemyScale, int x);
	virtual ~SwordEnemy();

	void changeState(const enemyStates state_);
	bool IsState(const enemyStates state_);
	bool StateEnd();

	void Update(float dt);

	void NotifyCollision(GameObject* other);
	void NotifyTileCollision(Collision::CollisionAxis collisionAxis);
	bool Is(std::string type);

	void TakeDamage(bool damage);

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
	Sound *kickhit, *punchhit;
	StateSwordEnemy* currentState;
	std::map<enemyStates, StateSwordEnemy*> enemyStatesMap;
	float distanceToBaon;
	bool collidedHorizontally;

	void InitializeStates();
	void InitializeSprite();
	void InitializeForces();
	void Initialize();
};

#endif /* SWORDENEMY_H_ */
