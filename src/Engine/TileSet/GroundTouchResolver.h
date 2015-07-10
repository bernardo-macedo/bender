/*
 * GroundTouchResolver.h
 *
 *  Created on: Jul 7, 2015
 *      Author: -Bernardo
 */

#ifndef ENGINE_TILESET_GROUNDTOUCHRESOLVER_H_
#define ENGINE_TILESET_GROUNDTOUCHRESOLVER_H_

#include "../Geometry/Rect.h"

class GroundTouchResolver {
public:
	GroundTouchResolver() {}
	virtual ~GroundTouchResolver() {}
	virtual bool IsTouchingGround(Rect rect, int scale) = 0;
	virtual float GetGroundHeight(float x) = 0;
};

#endif /* ENGINE_TILESET_GROUNDTOUCHRESOLVER_H_ */
