#ifndef INCLUDE_COLLISION_H
#define INCLUDE_COLLISION_H

#include "GameObject.h"
#include "Geometry/Rect.h"
/**
* Simple collision detection.
*/
/*class Collision {

	public:
		/**
		* Possible sides a rectangle can collide.
		*/
		/*enum RectangleSide : uint8_t {
			TOP = 0,
			BOTTOM,
			LEFT,
			RIGHT,
			NONE
		};


		static bool RectsCollided(GameObject* a_, TileSet* b_);
		/**
		* @return Whether two SDL_Rects collided.
		* @param a_ , b_ : The rectangles to check.
		*/
		//static bool RectsCollided(GameObject* a_, GameObject* b_);

		/**
		* @return The side (RectangleSide) which two SDL_Rects collided on.
		* @param a_ , b_ : The rectangles to check.
		*/
		//static RectangleSide RectsCollidedSide(const GameObject* a_, const GameObject* b_);

//};

#endif // INCLUDE_COLLISION_H
