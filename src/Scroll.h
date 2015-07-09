/*
 * Scroll.h
 *
 *  Created on: Jun 12, 2015
 *      Author: -Bernardo
 */

#ifndef SCROLL_H_
#define SCROLL_H_

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/InputManager.h"
#include "Engine/Sound.h"

class Scroll : public GameObject {
public:
	Scroll(int scale, int phase);
	virtual ~Scroll();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);

private:
	Sprite* sp;
	Sound *openSound, *closeSound;
	int phase;
	bool isOpen;
};

#endif /* SCROLL_H_ */
