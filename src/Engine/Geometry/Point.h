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
	Point(float x, float y);
	Point();

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	Point operator+(const Point& rhs) const {
	   return Point(x + rhs.x, y + rhs.y);
	}

	Point operator-(const Point& rhs) const {
	   return Point(x - rhs.x, y - rhs.y);
	}

	Point operator*(float rhs) const {
	   return Point(x*rhs, y*rhs);
	}
};

#endif /* ENGINE_GEOMETRY_POINT_H_ */
