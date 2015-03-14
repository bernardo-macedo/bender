/*
 * Body.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_PHYSICS_BODY_H_
#define ENGINE_PHYSICS_BODY_H_

#include "../Drawable.h"

class Body : public Drawable{
private:
	float velX, velY;
	float accelX, accelY;
public:
	Body(std::string id, float x, float y) : Drawable(id, x, y){
		velX = 0;
		velY = 0;
		accelX = 0;
		accelY = 0;
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
};

#endif /* ENGINE_PHYSICS_BODY_H_ */
