/*
 * Monumento.h
 *
 *  Created on: May 27, 2015
 *      Author: -Bernardo
 */

#ifndef MONUMENTO_H_
#define MONUMENTO_H_

#include <string>

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Camera.h"

#define MONUMENT_MAP_GROUND 512

class Monumento : public GameObject {
public:
	Monumento(int posX, int scale);
	virtual ~Monumento();

	virtual void Update(float dt);
	virtual bool IsDead();
	virtual void Render();
	virtual void NotifyCollision(GameObject* other);
	virtual bool Is(std::string type);
private:
	Sprite *sp;
};

#endif /* MONUMENTO_H_ */
