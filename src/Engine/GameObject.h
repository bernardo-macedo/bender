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
public:
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual bool IsDead() = 0;
	virtual void Render(int cameraY, int cameraX) = 0;

	Rect GetBox();
	void SetPos(int x, int y);
};

#endif /* ENGINE_GAMEOBJECT_H_ */
