/*
 * Minion.h
 *
 *  Created on: 24/04/2015
 *      Author: Pedro
 */

#ifndef MINION_H_
#define MINION_H_

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Bullet.h"
class Minion : public GameObject{
public:
	Minion(GameObject* minionCenter, float arcOffset = 0);
	virtual ~Minion();

	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);

	void Shoot(Point pos);
private:
	GameObject* center;
	Sprite *sp;
	float arc;
};

#endif /* MINION_H_ */
