/*
 * EndState.h
 *
 *  Created on: 22/05/2015
 *      Author: Pedro2
 */

#ifndef ENDSTATE_H_
#define ENDSTATE_H_
#include "Engine/State.h"
#include "Engine/Resources.h"
#include "Engine/Text.h"
#include "Engine/Music.h"
#include "StateData.h"
#include "Engine/InputManager.h"
#include "Engine/Sprite.h"


class EndState : public State{
private:
	Sprite *bg;
	Music *music;
	Text *instruction;
public:
	EndState(StateData *stateData);

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
};

#endif /* ENDSTATE_H_ */
