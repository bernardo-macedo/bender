/*
 * TitleState.h
 *
 *  Created on: 20/05/2015
 *      Author: Pedro2
 */

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "Engine/State.h"
#include "Engine/Sprite.h"
#include "Engine/Text.h"
#include "Engine/Timer.h"

class TitleState : public State{
public:
	enum STATES{WAITING, PRESSED};
	TitleState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
private:
	Sprite* bg;
	Text* title;
	Timer* timer;
	bool show;
	int count;
	float time;
	STATES state;
};

#endif /* TITLESTATE_H_ */
