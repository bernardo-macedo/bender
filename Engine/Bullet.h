/*
 * Bullet.h
 *
 *  Created on: 01/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_BULLET_H_
#define ENGINE_BULLET_H_

#include "Sprite.h"
#include "Geometry/Point.h"
#include "GameObject.h"
#include "math.h"

class Bullet : public GameObject{
private:
	Sprite *sp;
	Point speed;
	float distanceLeft;
public:
	bool targetsPlayer;

	Bullet(float x, float y, float angle, float speed,
			float maxDistance, std::string sprite, bool targets);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	virtual ~Bullet();
};

#endif /* ENGINE_BULLET_H_ */
