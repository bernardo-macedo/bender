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
#include "InputManager.h"
#include "Constants.h"

class Camera {
	static GameObject* focus;
public:
	static Point pos;
	static Point speed;

	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
};

#endif /* CAMERA_H_ */
