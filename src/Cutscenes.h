/*
 * Cutscenes.h
 *
 *  Created on: 13/07/2015
 *      Author: Pedro2
 */

#ifndef CUTSCENES_H_
#define CUTSCENES_H_

#include "Engine/State.h"
#include "Engine/Music.h"
#include "Engine/Timer.h"

class Cutscenes : public State {
public:
	Cutscenes();
	virtual ~Cutscenes();

	void ResolveDeadObject(GameObject* object);
	void OnUpdate(float dt, GameObject* object);
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	Sprite *c1, *c2, *c3;
	Music *music;
	Timer *t;
	int number;
};

#endif /* CUTSCENES_H_ */
