/*
 * Baon.h
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#ifndef BAON_H_
#define BAON_H_

#include <vector>
#include <memory>
#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Physics/Body.h"
#include "Engine/Timer.h"
#include "Being.h"
#include "Engine/Sound.h"
#include "Engine/TileSet/GroundTouchResolver.h"
#include "Lifebar.h"
#include "BendHUD.h"
#include "BaonAttack.h"
#include "EnemyAttack.h"

#define PLAYER_MAP_GROUND 425

class BaonStateManager;
class Baon : public Being {
public:
	enum baonStates {STAND, WALK, JUMP, RUN, FALLING};
	enum runController {NONE, PRERUNR, PRERUNL};
	Baon(int playerScale, float mapMax, int posX);
	virtual ~Baon();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision(Collision::CollisionAxis collisionAxis);
	bool IsDead();
	void SetDead(bool dead);
	bool Is(std::string type);
	bool IsDying();
	void SetDying(bool dying);
	BaonStateManager* GetState();

	void Run(bool flipped);
	void Walk(bool flipped);
	void Stand(bool flipped);
	void Land();
	void Jump(bool flipped);
	void Fall();
	void MidAir();
	void Punch();
	void Kick();
	void TakeDamage(EnemyAttack attack, bool damage, bool isFromRight);
	bool isTakingDamage();
	void TakeHit(bool flipped);
	bool IsCollisionFromRight();
	bool GetLevelWon();
	bool IsFalling();
	bool IsFlipped();
	void SetJumpFrame();

	// Cheats
	void SetSuperJump(bool superJump);
	void SetSuperSpeed(bool superSpeed);
	bool GetSuperJump();
	bool GetSuperSpeed();

	bool GetBendMode();
	void SetBendMode(bool bendMode_);
	bool IsCloseToEnemy();
	void SetCloseToEnemy(bool isClose);
	void RestoreLife();
	void SetTouchingGround(bool isTouchingGround);
	bool GetTouchingGround();
	Sound* GetStepSound(unsigned int stepNumber);
	void ResolveDeadReferences(int id);
	bool IsState(std::string name);

	BaonAttack GetLastGivenAttack();
	void SetLastGivenAttack(BaonAttack attack);

	void SetGroundTouchResolver(GroundTouchResolver* resolver);
	GroundTouchResolver* GetGroundTouchResolver();
	Sprite* GetSprite();

	int fallUpdateCount;
	BendHUD* bendHUD;

	bool isDamage;

private:
	static int WALK_SPEED;
	static int RUN_SPEED;
	static int JUMP_SPEED;
	static float DOUBLECLICK_TIME;
	static int MAX_HP;

	Sound *jump, *land, *step1, *step2, *kicks, *punchs;
	Sound *punchHit, *rockHit;

	// Cheats
	bool superJump;
	bool superSpeed;

	bool isDead;
	bool dying;
	bool takingDamage;
	bool closeToEnemy;
	bool levelWon;
	bool isFalling;
	bool isTouchingGround;

	Sprite *spBending;
	Sprite *sp;
	baonStates state;
	baonStates beforeJump;
	runController runStates;
	BaonAttack lastGivenAttack;
	EnemyAttack lastReceivedAttack;
	std::vector<int> spriteData;
	int numEst;
	bool flipped;
	Timer *t;
	BaonStateManager *stateManager;
	float limitX;
	float cameraLimitX;
	int hp;
	bool bendMode;
	bool damageDirectionRight;
	Lifebar *lifebar;

	GroundTouchResolver* resolver;

	void LoadSpriteData();
};

#endif /* BAON_H_ */
