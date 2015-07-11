/*
 * AbstractEnemy.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ABSTRACTENEMY_H_
#define ABSTRACTENEMY_H_

#include <map>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Timer.h"
#include "Engine/Camera.h"
#include "Engine/Physics/Physic.h"
#include "Being.h"
#include "BaonAttack.h"
#include "EnemyAttack.h"

class AbstractEnemy : public Being {
public:
	enum runController {NONE, PRERUNR, PRERUNL};

	AbstractEnemy(int enemyScale, int x, int hp, int walkSpeed, int runSpeed, float doubleClickTime);
	virtual ~AbstractEnemy();

	virtual void Update(float dt) = 0;
	virtual void NotifyCollision(GameObject* other) = 0;
	virtual void NotifyTileCollision(Collision::CollisionAxis collisionAxis) = 0;

	virtual void Render();
	virtual bool IsDead();
	virtual bool Is(std::string type);

	virtual void TakeDamage(BaonAttack attack) = 0;
	virtual void Run(bool flipped);
	virtual void Walk(bool flipped);
	virtual void Stand(bool flipped);
	virtual void Jump(bool flipped);

	Sprite* GetSprite();
	Timer* GetTimer();
	int GetSpawnX();
	int GetHP();
	bool GetFlipped();
	bool IsTakingDamage();
	bool IsRemovable();
	bool IsCollisionFromRight();
	bool IsDying();

	bool IsCloseToBaon();
	void SetCloseToBaon(bool close);
	void SetTakingDamage(bool damage);
	void SetDying(bool dying);
	void SetDead(bool isDead);
	void SetFlipped(bool flipped);
	EnemyAttack GetLastGivenAttack();
	void SetLastGivenAttack(EnemyAttack attack);

	virtual void SetWalkSprite() = 0;
	virtual void SetStandSprite() = 0;
	virtual void SetJumpSprite() = 0;
	virtual void SetTakingDamageSprite() = 0;
	virtual void SetDyingSprite() = 0;

	bool isDamage;

protected:
	int WALK_SPEED_E;
	int RUN_SPEED_E;
	float DOUBLECLICK_TIME;
	static int ENEMY_MAP_GROUND;

	Sprite *sp;
	Timer *t;
	runController runStates;
	EnemyAttack lastGivenAttack;
	std::vector<int> spriteData;
	int numEst;
	bool flipped;
	bool closeToBaon;
	bool isDead;
	bool isDying;
	bool isRemovable;
	int fallUpdateCount;
	bool isTakingDamage;
	int spawnX;
	int hp;
	bool collisionFromRight;

	virtual void InitializeStates() = 0;
	virtual void InitializeSprite() = 0;
	virtual void InitializeForces() = 0;
	virtual void Initialize() = 0;

	void LoadSpriteData(std::string file);
};

#endif /* ABSTRACTENEMY_H_ */
