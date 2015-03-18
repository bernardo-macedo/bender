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
#include "GameObject.h"

class State {
private:
	bool quitRequested;
	std::list<GameObject*> board;
	SDL_Event event;
public:
	virtual void Setup() = 0;
	virtual void OnRender() = 0;
	virtual void ClearScreen(int red, int green, int blue, int alpha);

	/*Events*/
	virtual void OnMouseDown(SDL_Event event) = 0;

	State();
	virtual ~State();

	void Add(GameObject* go);
	Drawable* GetById(std::string id);
	bool QuitRequested();
	void Update();
	void Render();
	void initialize();
	void ProcessEvents();
};

#endif /* ENGINE_STATE_H_ */
