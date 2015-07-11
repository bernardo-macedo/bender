/*
 * PedraDefesa.h
 *
 *  Created on: 10/07/2015
 *      Author: Pedro2
 */

#ifndef PEDRADEFESA_H_
#define PEDRADEFESA_H_

#include <string>

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Timer.h"

class PedraDefesa : public GameObject{
public:
	PedraDefesa(int x, int y);
	virtual ~PedraDefesa();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
private:
	Timer* t;
	Sprite* sp;
	bool dead;
};

#endif /* PEDRADEFESA_H_ */
