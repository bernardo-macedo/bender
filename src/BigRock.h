/*
 * BigRock.h
 *
 *  Created on: 13/07/2015
 *      Author: Pedro2
 */

#ifndef BIGROCK_H_
#define BIGROCK_H_

#include <string>

#include "Being.h"
#include "Engine/Sprite.h"
#include "Engine/Timer.h"

class BigRock : public Being{
public:
	BigRock(int x, int y);
	virtual ~BigRock();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision(Collision::CollisionAxis collisionAxis);

	bool Is(std::string type);
	bool finnished();
	void SetFlipped(bool flipped);
private:
	Sprite *sp;
	Timer *t;
	bool dead, finnishedLifting, flipped;
};

#endif /* BIGROCK_H_ */
