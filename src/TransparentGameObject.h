/*
 * TransparentGameObject.h
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#ifndef TRANSPARENTGAMEOBJECT_H_
#define TRANSPARENTGAMEOBJECT_H_

#include "Engine/GameObject.h"

class TransparentGameObject : public GameObject{
public:
	TransparentGameObject(int x, int y, int w, int h, bool right);

	virtual void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);

	void SetDead(bool dead);
	bool IsRight();

private:
	bool dead;
	bool right;
};

#endif /* TRANSPARENTGAMEOBJECT_H_ */
