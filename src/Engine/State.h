/*
 * State.h
 *
 *  Created on: 19/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_STATE_H_
#define ENGINE_STATE_H_

#include <vector>

#include "../Being.h"
#include "TileSet/TileMap.h"
#include "../EnemyAIManager.h"

class State {
protected:
	TileMap* tileMap;
	std::vector<std::unique_ptr<GameObject>> objectArray;
	bool popRequested;
	bool quitRequested;
	int initialPositionX;
	int slowMotion;

	virtual void ResolveDeadObject(GameObject* object) = 0;
	virtual void OnUpdate(float dt, GameObject* object) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	void SetSlowMotion(int slow);
public:
	State(int posX = -1);
	virtual ~State();

	void UpdateArray(float dt);
	void RenderArray();

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	void AddObject(GameObject* object);

	bool PopRequested();
	bool QuitRequested();

	GameObject* FindByID(int id);

};

#endif /* ENGINE_STATE_H_ */
