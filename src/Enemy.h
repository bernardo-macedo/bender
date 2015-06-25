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
#include "Engine/Sound.h"

#define ENEMY_MAP_GROUND 143

class StateEnemy;

class Enemy : public Being {
public:
	enum enemyStates {STAND, WALK, JUMP, RUN, FALLING, PATROLLING, FOLLOW, PUNCH, BEND, TAKINGHIT};
	enum runController {NONE, PRERUNR, PRERUNL};
	Enemy(int enemyScale, int x);
	virtual ~Enemy();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision();
	bool IsDead();
	bool Is(std::string type);
	bool GetFlipped();

	Sprite* GetSprite();

	void Run(bool flipped);
	void Walk(bool flipped);
	void Stand(bool flipped);
	void Jump(bool flipped);

	void changeState(const enemyStates state_);
	bool IsState(const enemyStates state_);
	bool StateEnd();
	bool isDamage;
	Timer* Time();
	void TakeDamage(bool damage);
	void SetTakingDamage(bool damage);

	bool IsTakingDamage();
	void SetDead(bool isDead_);
	bool IsRemovable();
	bool IsCloseToBaon();
	void SetCloseToBaon(bool close);
	float GetCoolDown();
	void SetCoolDown(float coolDown);
	int GetSpawnX();
	bool IsCollisionFromRight();

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
	bool isRemovable;
	int fallUpdateCount;
	bool isTakingDamage;
	bool closeToBaon;
	float bendCoolDown;
	int spawnX;
	int hp;
	bool collisionFromRight;

	Sound *kickhit, *punchhit;
	void InitializeStates();

};

#endif /* ENEMY_H_ */
