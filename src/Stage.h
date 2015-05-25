/*
 * Stage.h
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#ifndef STAGE_H_
#define STAGE_H_

#include "Engine/State.h"
#include "Baon.h"

class Stage : public State{
public:
	Stage();

	void Update(float dt);
	void Render();

	void Pause() ;
	void Resume();
private:
	Baon* baon;
	Sprite *sp;
};

#endif /* STAGE_H_ */
