/*
 * MenuPrincipal.h
 *
 *  Created on: Jun 25, 2015
 *      Author: -Bernardo
 */

#ifndef MENUPRINCIPAL_H_
#define MENUPRINCIPAL_H_

#include <stdio.h>
#include <vector>
#include <map>
#include "Engine/Sprite.h"
#include "Engine/InputManager.h"

class MenuPrincipal {
public:
	MenuPrincipal(int scale);
	virtual ~MenuPrincipal();

	void Update(float dt);
	void Render();
	int GetSelectedButton();

private:
	Sprite *sp;
	std::vector<int> spriteData;
	int numButtons;
	int selectedButton;
	int scale;

	void LoadSpriteData();
};

#endif /* MENUPRINCIPAL_H_ */
