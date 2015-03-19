/*
 * Point.h
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GEOMETRY_POINT_H_
#define ENGINE_GEOMETRY_POINT_H_

class Point {
private:
	float x,y;
public:
	virtual ~Point();

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
};

#endif /* ENGINE_GEOMETRY_POINT_H_ */
