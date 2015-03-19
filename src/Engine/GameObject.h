/*
 * GameObject.h
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GAMEOBJECT_H_
#define ENGINE_GAMEOBJECT_H_

#include <iostream>

class GameObject{
private:
	Rect box;
public:
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual bool IsDead() = 0;
	virtual void Render() = 0;

	Rect GetBox();
};

#endif /* ENGINE_GAMEOBJECT_H_ */
