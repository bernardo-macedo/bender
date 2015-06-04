/*
 * Rect.h
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GEOMETRY_RECT_H_
#define ENGINE_GEOMETRY_RECT_H_
#include "Point.h"
#include <math.h>

class Rect {
private:
	float x,y, w, h;
public:
	virtual ~Rect();

	float GetX() const;
	void SetX(float x);
	float GetY() const;
	void SetY(float y);

	float GetW() const;
	void SetW(float w);
	float GetH() const;
	void SetH(float h);

	Point GetCenter();

	bool IsInside(float mouseX, float mouseY);
	Point Intersection(Rect other);

};

inline bool operator==(const Rect& rect, const Rect& other) {
		return  rect.GetX() == other.GetX() && rect.GetY() == other.GetY()
				&& rect.GetW() == other.GetW() && rect.GetH() == other.GetH();
	}

#endif /* ENGINE_GEOMETRY_RECT_H_ */
