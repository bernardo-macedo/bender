/*
 * Drone.h
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#ifndef DRONE_H_
#define DRONE_H_

#include "Engine/Geometry/Rectangle.h"
#include "Engine/Sprite.h"
class Drone : public Sprite{
private:
public:
	static int WIDTH;
	static int HEIGHT;

	Drone(std::string id, float x, float y) : Sprite(id, x, y){
		Open("ocean.jpg");
		SetClip(0, 0, WIDTH, HEIGHT);
	}
	void Update();
	bool IsDead();
	virtual ~Drone();

	Sprite* GetSprite();
};

#endif /* DRONE_H_ */
