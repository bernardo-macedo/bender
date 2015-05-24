/*
 * Penguins.h
 *
 *  Created on: 12/05/2015
 *      Author: Pedro2
 */

#ifndef PENGUINS_H_
#define PENGUINS_H_

#include "Engine/GameObject.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Physics/Body.h"
#include "Engine/Sprite.h"
#include "Engine/Sound.h"
class Penguins : public GameObject{
public:
	Penguins(float x, float y);
	virtual ~Penguins();

	void Update(float dt);
	void Render();
	bool IsDead();
	bool Is(std::string type);
	void NotifyCollision(GameObject* other);

	void Shoot();
	static Penguins* player;
private:
	Sprite *bodySP, *cannonSP;
	Point speed;
	float linearSpeed;
	float cannonAngle;
	int hp;
	Body *body;
	Sound* explosion;
};

#endif /* PENGUINS_H_ */
