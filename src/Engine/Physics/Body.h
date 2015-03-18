/*
 * Body.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_PHYSICS_BODY_H_
#define ENGINE_PHYSICS_BODY_H_

#include "../Drawable.h"
#include "Force.h"
#include <list>

class Body : public Drawable{
private:
	float velX, velY;
	float accelX, accelY;

	float angularVel, angularAccel;
	std::list<Force*> forces;
public:
	Body(std::string id, float x, float y) : Drawable(id, x, y){
		velX = 0;
		velY = 0;
		accelX = 0;
		accelY = 0;
		angularVel = 0;
		angularAccel = 0;
		SetPhysicalBody(true);
	}
	virtual ~Body();

	float getAccelX() const;
	void setAccelX(float accelX);
	float getAccelY() const;
	void setAccelY(float accelY);
	float getVelX() const;
	void setVelX(float velX);
	float getVelY() const;
	void setVelY(float velY);
	void SetAngularVel(float vel);
	float GetAngularVel();
	void SetAngularAccel(float accel);
	float GetAngularAccel();


	std::list<Force*> GetForces();
	void ApplyForce(Force* f);
	void removeForce(std::string id);
};

#endif /* ENGINE_PHYSICS_BODY_H_ */
