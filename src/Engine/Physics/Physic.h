/*
 * Physic.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_PHYSICS_PHYSIC_H_
#define ENGINE_PHYSICS_PHYSIC_H_

#include "Body.h"

class Physic {
public:
	static Physic* instance;
	void UpdatePhysic(Body* b);
	Physic();
	virtual ~Physic();
	static Physic* GetInstance();
};

#endif /* ENGINE_PHYSICS_PHYSIC_H_ */
