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
	enum HudAttack {ONE, TWO, THREE, FOUR, FIVE, SIX};

	static Hud* GetInstance(int scale, int level);
	static Hud* GetInstance();
	virtual ~Hud();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	void SetBuffering(HudAttack hudAttackNumber);
	bool IsBuffering(HudAttack hudAttackNumber);
	void SetLevel(int level);

private:
	static Hud* instance;
	Sprite hud;
	std::vector<CoolDown> hudItems;
	bool bufferingAttacks[6];
	int level;
	int scale;

	Hud(int scale, int level);
	bool IsValidAttack(HudAttack hudAttackNumber);
};

#endif /* HUD_H_ */
