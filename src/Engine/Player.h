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
#include "Geometry/Point.h"
#include "InputManager.h"
#include "Animation.h"
#include "Camera.h"
#include <queue>

#define MAX_SPEED 500.0
#define ACCELERATION 1000.0
#define GRAVITY 1500.0
#define JUMP 80000.0
#define JUMP_SPEED_CUT 1000
#define FRICTION 3.5
#define MAX_ANIMATION_TIME 400

class Player : public GameObject {
private:
	Sprite* sp;
	Point speed;
	Point acceleration;
	int hp;
	Animation* animation;
	bool onGround;
	const int pulando = 0, caindo = 1, nochao = 2;

public:
	int state;

	Player(float x, float y, Animation* anim = NULL);
	virtual ~Player();
	void Update(float dt);
	void Render();
	bool IsDead();
	void SetOnGround(bool onGround) {
		this->onGround = onGround;
	}
};

#endif /* ENGINE_PLAYER_H_ */
