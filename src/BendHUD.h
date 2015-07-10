/*
 * BendHUD.h
 *
 *  Created on: Jun 22, 2015
 *      Author: Simiao
 */

#ifndef BENDHUD_H_
#define BENDHUD_H_

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"
#include "Engine/Timer.h" 
 
class BendHUD : public GameObject {
public:
	BendHUD(int scale);
	virtual ~BendHUD();

	virtual void Update(float dt);
	virtual void Render();
	virtual void NotifyCollision(GameObject* other);
	virtual void NotifyTileCollision();
	virtual bool IsDead();

	virtual bool Is(std::string type);
	int GetScale();

	void Hide();
	void Show();

private:
	enum Arrows {UP, RIGHT, DOWN, LEFT};

	int scale;
	Sprite* sp;
	Sprite* active[4];
	bool activeHide[4];
	Timer* activeTime[4];

	bool isHidden;
};

#endif /* BENDHUD_H_ */
