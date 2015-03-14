/*
 * Drone.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef DRONE_H_
#define DRONE_H_

#include "Engine/Physics/Body.h"
#include "Engine/GameRenderer.h"

class Drone: public Body {
public:
	Drone(std::string id, float x, float y) : Body(id, x, y){ }
	virtual ~Drone();

	void OnRender();
};

#endif /* DRONE_H_ */
