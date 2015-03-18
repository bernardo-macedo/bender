/*
 * GameObject.h
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GAMEOBJECT_H_
#define ENGINE_GAMEOBJECT_H_

#include <iostream>
#include "Physics/BOdy.h"

class GameObject : public Body{
public:
	GameObject(std::string id, float x, float y) : Body(id, x, y){

	}
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual bool IsDead() = 0;

};

#endif /* ENGINE_GAMEOBJECT_H_ */
