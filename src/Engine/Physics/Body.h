/*
 * Body.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_PHYSICS_BODY_H_
#define ENGINE_PHYSICS_BODY_H_

#include "Force.h"
#include <list>

class Body{
private:
	float x, y;
	float velX, velY;
	float accelX, accelY;
	float resistance;

	float rotation, angularVel, angularAccel;
	std::list<Force*> forces;
public:
	Body(std::string id, float x, float y){
		velX = 0;
		velY = 0;
		accelX = 0;
		accelY = 0;
		angularVel = 0;
		angularAccel = 0;
		rotation = 0;
		resistance = 1;
		this->x = x;
		this->y = y;
	}
	virtual ~Body();

	float GetAccelX();
	void SetAccelX(float accelX);
	float GetAccelY();
	void SetAccelY(float accelY);
	float GetVelX();
	void SetVelX(float velX);
	float GetVelY();
	void SetVelY(float velY);
	void SetAngularVel(float vel);
	float GetAngularVel();
	void SetAngularAccel(float accel);
	float GetAngularAccel();
	float GetRotation();
	void SetRotation(float r);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	float GetResistance();
	void SetResistance(float r);

	std::list<Force*> GetForces();
	void ApplyForce(Force* f);
	void removeForce(std::string id);
	Force* GetForce(std::string id);
};

#endif /* ENGINE_PHYSICS_BODY_H_ */
