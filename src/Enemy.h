/*
 * Enemy.h
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Physics/Body.h"
#include "Engine/Timer.h"

#define MAP_GROUND 500

class Enemy : public GameObject {
public:
	enum enemyStates {STAND, WALK, JUMP, RUN, FALLING};
	enum runController {NONE, PRERUNR, PRERUNL};
	Enemy();

	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	bool IsDead();
	bool Is(std::string type);

	void Run(bool flipped);
	void Walk(bool flipped);
	void Stand(bool flipped);
	void Jump(bool flipped);
private:
	int WALK_SPEED_E;
	int RUN_SPEED_E;
	float DOUBLECLICK_TIME;

	Sprite *sp;
	enemyStates state;
	runController runStates;
	std::vector<int> spriteData;
	int numEst;
	bool flipped;
	Body *b;
	Timer *t;
	int fallUpdateCount;
};

#endif /* ENEMY_H_ */
