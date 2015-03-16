/*
 * Force.h
 *
 *  Created on: 15/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_PHYSICS_FORCE_H_
#define ENGINE_PHYSICS_FORCE_H_
#include <iostream>

class Force {
private:
	float x, y;
	std::string id;
public:
	Force(std::string id, float x, float y);
	virtual ~Force();

	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);
	std::string GetId();
};

#endif /* ENGINE_PHYSICS_FORCE_H_ */
