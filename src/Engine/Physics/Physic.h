/*
 * Physic.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_PHYSICS_PHYSIC_H_
#define ENGINE_PHYSICS_PHYSIC_H_
#include <iostream>
#include <list>
#include "Body.h"
#include "Force.h"

class Physic {
public:
	static Physic* instance;
	void UpdatePhysic(Body* b, float dt);
	Physic();
	virtual ~Physic();
	static Physic* GetInstance();
};

#endif /* ENGINE_PHYSICS_PHYSIC_H_ */
