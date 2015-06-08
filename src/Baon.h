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

#define PLAYER_MAP_GROUND 425

class BaonStateManager;
class Baon : public Being {
public:
	enum baonStates {STAND, WALK, JUMP, RUN, FALLING};
	enum runController {NONE, PRERUNR, PRERUNL};
	Baon(int playerScale, float mapMax);
	virtual ~Baon();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision();
	bool IsDead();
	bool Is(std::string type);
	BaonStateManager* GetState();

	void Run(bool flipped);
	void Walk(bool flipped);
	void Stand(bool flipped);
	void Jump(bool flipped);
	void Fall();
	void MidAir();
	void Punch();
	void Kick();

	// Cheats
	void SetSuperJump(bool superJump);
	void SetSuperSpeed(bool superSpeed);
	bool GetSuperJump();
	bool GetSuperSpeed();

	Sprite* GetSprite();

	int fallUpdateCount;

	bool isDamage;

private:
	static int WALK_SPEED;
	static int RUN_SPEED;
	static int JUMP_SPEED;
	static float DOUBLECLICK_TIME;

	// Cheats
	bool superJump;
	bool superSpeed;

	Sprite *sp;
	baonStates state;
	baonStates beforeJump;
	runController runStates;
	std::vector<int> spriteData;
	int numEst;
	bool flipped;
	Timer *t;
	BaonStateManager *stateManager;
	float limitX;
	float cameraLimitX;

	void LoadSpriteData();
};

#endif /* BAON_H_ */
