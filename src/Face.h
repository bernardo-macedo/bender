/*
 * Face.h
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#ifndef FACE_H_
#define FACE_H_

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"

class Face : public GameObject{
private:
	int hitPoints;
	Sprite* sp;

public:
	Face(int x, int y);
	virtual ~Face();

	void Damage(int damage);

	void Update();
	void Render();
	bool IsDead();
};

#endif /* FACE_H_ */
