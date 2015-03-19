/*
 * Rect.h
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GEOMETRY_RECT_H_
#define ENGINE_GEOMETRY_RECT_H_

class Rect {
private:
	float x,y, w, h;
public:
	virtual ~Rect();

	float GetX();
	void SetX(float x);
	float GetY();
	void SetY(float y);

	float GetW();
	void SetW(float w);
	float GetH();
	void SetH(float h);

};

#endif /* ENGINE_GEOMETRY_RECT_H_ */
