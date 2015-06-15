/*
 * Hud.h
 *
 *  Created on: Jun 15, 2015
 *      Author: -Bernardo
 */

#ifndef HUD_H_
#define HUD_H_

#include <vector>
#include "Engine/Game.h"
#include "Engine/GameObject.h"
#include "CoolDown.h"

class Hud : public GameObject {
public:
	Hud(int scale, int phase);
	virtual ~Hud();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);

private:
	Sprite hud;
	std::vector<CoolDown> hudItems;
};

#endif /* HUD_H_ */
