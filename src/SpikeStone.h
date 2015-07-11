/*
 * SpikeStone.h
 *
 *  Created on: 07/07/2015
 *      Author: Pedro2
 */

#ifndef SPIKESTONE_H_
#define SPIKESTONE_H_

#include "Being.h"
#include <string>

#include "Engine/Camera.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Physic.h"
#include "Engine/Sprite.h"
#include "Engine/Geometry/Rect.h"
#include "TransparentGameObject.h"
#include "Engine/Timer.h"

class SpikeStone : public Being{
public:
	SpikeStone(int x, int y, int scale, bool flipped);
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision(Collision::CollisionAxis collisionAxis);
	bool IsDead();

	bool IsRight();
	void SetFlipped(bool fllipped);
	bool GetFlipped();

	virtual bool Is(std::string type);
private:
	Sprite *sp;
	int scale;
	bool dead;
	bool flipped;
	bool right;
	TransparentGameObject* transp;
	bool transpSet;
	Timer* t;
};

#endif /* SPIKESTONE_H_ */
