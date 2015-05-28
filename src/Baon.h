/*
 * Baon.h
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#ifndef BAON_H_
#define BAON_H_

#include <vector>

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Physics/Body.h"
#include "Engine/Timer.h"

#define PLAYER_MAP_GROUND 425

class BaonStateManager;
class Baon : public GameObject {
public:
	enum baonStates {STAND, WALK, JUMP, RUN, FALLING};
	enum runController {NONE, PRERUNR, PRERUNL};
	Baon();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision();
	bool IsDead();
	bool Is(std::string type);
	Body* GetBody();

	void Run(bool flipped);
	void Walk(bool flipped);
	void Stand(bool flipped);
	void Jump(bool flipped);
	void Fall();
	void MidAir();
	void Punch();
	void Kick();

	int fallUpdateCount;


private:
	static int WALK_SPEED;
	static int RUN_SPEED;
	static float DOUBLECLICK_TIME;

	Sprite *sp;
	baonStates state;
	baonStates beforeJump;
	runController runStates;
	std::vector<int> spriteData;
	int numEst;
	bool flipped;
	Body *b;
	Timer *t;
	BaonStateManager *stateManager;
};

#endif /* BAON_H_ */
