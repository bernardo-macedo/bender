/*
 * Rect.h
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GEOMETRY_RECTANGLE_H_
#define ENGINE_GEOMETRY_RECTANGLE_H_

#include <iostream>

#include "../GameObject.h"

class Rectangle : public GameObject{
private:
	float w;
	float h;
public:
	Rectangle(std::string id, float x, float y, float w, float h) : GameObject(id, x, y){
		this->w = w;
		this->h = h;
	}

	virtual ~Rectangle();

	void OnRender();
};

#endif /* ENGINE_PHYSICS_RECTANG*/

