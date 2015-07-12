/*
 * GameObject.h
 *
 *  Created on: 17/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_GAMEOBJECT_H_
#define ENGINE_GAMEOBJECT_H_

#include <iostream>
#include "Geometry/Rect.h"

class GameObject{
protected:
	Rect box;
	int id;
public:
	static const int PEDRA_BASICO_BAON;
	static const int PEDRA_BASICO_PULO_BAON;
	static const int SPIKE_STONE_BAON;
	static const int PEDRA_BASICO_ENEMY;
	static const int BAON;
	static const int ENEMY;
	static const int SWORD_ENEMY;
	static const int BIG_ENEMY;
	static const int TRANSPARENT_GAME_OBJECT;
	static const int PEDRA_DEFESA;

	virtual ~GameObject();

	virtual void Update(float dt) = 0;
	virtual bool IsDead() = 0;
	virtual void Render() = 0;
	virtual void NotifyCollision(GameObject* other) = 0;
	virtual bool Is(std::string type) = 0;
	virtual int GetAngle();

	Rect GetBox();
	void SetPos(int x, int y);
	void SetPosX(int x);
	void SetPosY(int y);
	int GetID();
	void SetID(int i);

	float rotation;
};

#endif /* ENGINE_GAMEOBJECT_H_ */
