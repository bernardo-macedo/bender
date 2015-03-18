/*
 * Drone.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef DRONE_H_
#define DRONE_H_

#include "Engine/Geometry/Rectangle.h"
class Drone : public Rectangle{
public:
	static int WIDTH;
	static int HEIGHT;

	Drone(std::string id, float x, float y) : Rectangle(id, x, y, WIDTH, HEIGHT){}
	void Update();
	bool IsDead();
	virtual ~Drone();
};

#endif /* DRONE_H_ */
