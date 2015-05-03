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
#include "Engine/Physics/Body.h"
class Minion : public GameObject{
public:
	Minion(float x, float y);
	virtual ~Minion();

	void Update(float dt);
	void Render();
	bool IsDead();
	Body* GetBody();
	void SetBody(Body* b);

	void Shoot();
private:
	float walkForceLeft, walkForceRight;
	Sprite *sp;
	Body* b;
};

#endif /* MINION_H_ */
