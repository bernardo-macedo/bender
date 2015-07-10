/*
 * Collision.h
 *
 *  Created on: 13/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_COLLISION_H_
#define ENGINE_COLLISION_H_

#include <cmath>
#include <algorithm>

#include "Geometry/Rect.h"

class Collision {
public:
	enum CollisionAxis {AXIS_X, AXIS_Y};

	static inline bool IsColliding(Rect a, Rect b, float angleOfA, float angleOfB) {
		Point A[] = { Point( a.GetX(), a.GetY() + a.GetH() ),
					  Point( a.GetX() + a.GetW(), a.GetY() + a.GetH() ),
					  Point( a.GetX() + a.GetW(), a.GetY() ),
					  Point( a.GetX(), a.GetY() )
					};
		Point B[] = { Point( b.GetX(), b.GetY() + b.GetH() ),
					  Point( b.GetX() + b.GetW(), b.GetY() + b.GetH() ),
					  Point( b.GetX() + b.GetW(), b.GetY() ),
					  Point( b.GetX(), b.GetY() )
					};

		for (auto& v : A) {
			v = Rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
		}

		for (auto& v : B) {
			v = Rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();
		}

		Point axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

		for (auto& axis : axes) {
			float P[4];

			for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

			float minA = *std::min_element(P, P + 4);
			float maxA = *std::max_element(P, P + 4);

			for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

			float minB = *std::min_element(P, P + 4);
			float maxB = *std::max_element(P, P + 4);

			if (maxA < minB || minA > maxB)
				return false;
		}

		return true;
	}

private:

	static inline float Mag(Point& p) {
		return std::sqrt(p.getX() * p.getX() + p.getY() * p.getY());
	}

	static inline Point Norm(Point p) {
		return p * (1.f / Mag(p));
	}

	static inline float Dot(Point& a, Point& b) {
		return a.getX() * b.getX() + a.getY() * b.getY();
	}

	static inline Point Rotate(Point p, float angle) {
		float cs = std::cos(angle), sn = std::sin(angle);
		return Point ( p.getX() * cs - p.getY() * sn, p.getX() * sn + p.getY() * cs );
	}
};

#endif /* ENGINE_COLLISION_H_ */
