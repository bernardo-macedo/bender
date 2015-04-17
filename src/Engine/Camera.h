/*
 * Camera.h
 *
 *  Created on: 16/04/2015
 *      Author: Pedro
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <stdlib.h>
#include "Geometry/Point.h"
#include "GameObject.h"

class Camera {
	GameObject* focus;
public:
	Point pos;
	Point speed;

	void Follow(GameObject* newFocus);
	void Unfollow();
	void Update(float dt);
};

#endif /* CAMERA_H_ */
