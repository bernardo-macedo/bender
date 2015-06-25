/*
 * TitleState.h
 *
 *  Created on: May 19, 2015
 *      Author: -Bernardo
 */

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "Engine/State.h"
#include "Engine/Sprite.h"
#include "Engine/InputManager.h"
#include "Stage.h"
#include "Engine/Game.h"
#include "Engine/Text.h"
#include "MenuPrincipal.h"

class TitleState : public State {
private:
	Sprite bg;
	MenuPrincipal* menu;

public:
	TitleState();
	virtual ~TitleState();

	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
};

#endif /* TITLESTATE_H_ */
