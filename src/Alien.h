/*
 * Alien.h
 *
 *  Created on: 24/04/2015
 *      Author: Pedro
 */

#ifndef ALIEN_H_
#define ALIEN_H_

#include "SDL.h"
#include "Engine/GameObject.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Sprite.h"
#include "Minion.h"
#include "Engine/Timer.h"
#include <queue>
#include <vector>
#include "Engine/Sound.h"

class Alien : public GameObject{
private:
	class Action{
	public:
		enum ActionType{
			MOVE = 0,
			SHOOT,
		};
		Action(ActionType type, float x, float y){
			this->type = type;
			pos = new Point();
			pos->setX(x);
			pos->setY(y);
		}
		ActionType type;
		Point *pos;
	};

	Sprite *sp;
	Point speed;
	int hp;

	std::queue<Action> taskQueue;
	std::vector<Minion*> minionArray;
	Minion* m;
	static int alienCount;
	enum AlienState{MOVING, RESTING};
	AlienState alienState;
	Timer *shootCoolDown;
	Sound* explosion;
public:
	Alien(float x, float y, int nMinions, int id);
	virtual ~Alien();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
};

#endif /* ALIEN_H_ */
