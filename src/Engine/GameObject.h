/*
 * GameObject.h
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GAMEOBJECT_H_
#define ENGINE_GAMEOBJECT_H_

#include <iostream>
#include "Geometry/Rect.h"

class GameObject{
protected:
	Rect box;
	int id;
public:
	virtual ~GameObject();

	virtual void Update(float dt) = 0;
	virtual bool IsDead() = 0;
	virtual void Render() = 0;
	virtual void NotifyCollision(GameObject* other) = 0;
	virtual bool Is(std::string type) = 0;
	virtual int GetAngle();

	Rect GetBox();
	void SetPos(int x, int y);
	int GetID();

	float rotation;
};

#endif /* ENGINE_GAMEOBJECT_H_ */
