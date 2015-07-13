/*
 * PedraBasico.h
 *
 *  Created on: 14/06/2015
 *      Author: Pedro2
 */

#ifndef PEDRABASICO_H_
#define PEDRABASICO_H_

#include <string>

#include "Being.h"
#include "Engine/Sprite.h"

class RockDeathListener {
public:
	RockDeathListener() {}
	virtual ~RockDeathListener() {}
	virtual void OnRockDead() = 0;
};

class PedraBasico : public Being {
private:
	Sprite* sp;
	RockDeathListener* listener;
	bool collided;
	bool goingLeft;
	int limitX;
	float limitY;
	bool thrown;
	bool dead;
public:
	PedraBasico(int x, int y, int scale, RockDeathListener* listener);
	virtual ~PedraBasico();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision(Collision::CollisionAxis collisionAxis);
	bool Is(std::string type);
	bool IsFinnished();
	bool IsGoingLeft();
	void SetGoingLeft(bool left);
	void SetLimitX(int limit);
	bool GetLimitX();
	void SetLimitY(float y);
	bool Isthrown();
	void SetThrown(bool thrown);
	void SetDead(bool dead);
	void SetRockSprite(float speed);
	void SetJumpRockSprite();
	int GetCurrentFrame();
};

#endif /* PEDRABASICO_H_ */
