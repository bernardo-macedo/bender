/*
 * Point.h
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GEOMETRY_POINT_H_
#define ENGINE_GEOMETRY_POINT_H_

#include <math.h>

class Point {
private:
	float x,y;
public:
	Point(float x = 0, float y = 0);
	virtual ~Point();

	Point operator+(Point other);
	void operator+=(Point other);
	Point operator-(Point other);
	void operator-=(Point other);
	Point operator*(float scalar);
	void operator*=(float scalar);
	float operator*(Point other);

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float distance(Point other);
};

#endif /* ENGINE_GEOMETRY_POINT_H_ */
