/*
 * Player.h
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#ifndef ENGINE_PLAYER_H_
#define ENGINE_PLAYER_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Point.h"
#include <queue>


class Player : public GameObject {
private:
	class Action {

	};
private:
	Sprite* sp;
	Point speed;
	int hp;

	std::queue<Action> taskQueue;
public:
	Player(float x, float y);
	virtual ~Player();
	void Update(float dt);
	void Render();
	bool IsDead();
};

#endif /* ENGINE_PLAYER_H_ */
