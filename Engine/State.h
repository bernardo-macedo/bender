/*
 * State.h
 *
 *  Created on: 19/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_STATE_H_
#define ENGINE_STATE_H_

#include <vector>
#include <memory>
#include <iostream>

#include "GameObject.h"

class State {
protected:
	void UpdateArray(float dt);
	void RenderArray();

	bool popRequested;
	bool quitRequested;

	std::vector<std::unique_ptr<GameObject>> objectArray;
public:
	State();
	virtual ~State();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	void AddObject(GameObject* object);

	bool PopRequested();
	bool QuitRequested();

	GameObject* FindByID(int id);

};

#endif /* ENGINE_STATE_H_ */
