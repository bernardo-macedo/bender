/*
 * State.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_STATE_H_
#define ENGINE_STATE_H_
#include <list>

#include "SDL.h"
#include "Sprite.h"
#include "Drawable.h"

class State {
private:
	Sprite* bg;
	bool quitRequested;
	std::list<Drawable*> board;
public:
	virtual void Setup() = 0;
	virtual void OnRender() = 0;

	State();

	void Add(Drawable* d);
	Drawable* GetById(std::string id);
	bool QuitRequested();
	void Update();
	void Render();
	void initialize();
};

#endif /* ENGINE_STATE_H_ */
