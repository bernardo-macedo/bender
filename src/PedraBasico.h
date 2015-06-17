/*
 * PedraBasico.h
 *
 *  Created on: 14/06/2015
 *      Author: Pedro2
 */

#ifndef PEDRABASICO_H_
#define PEDRABASICO_H_

#include <string>

#include "Being.h"
#include "Engine/Sprite.h"

class PedraBasico : public Being{
private:
	Sprite* sp;
	bool collided;
public:
	PedraBasico(int x, int y, int scale);
	virtual ~PedraBasico();

	void Update(float dt);
	bool IsDead();
	void Render();
	void NotifyCollision(GameObject* other);
	void NotifyTileCollision();
	bool Is(std::string type);
	Sprite* GetSprite();
};

#endif /* PEDRABASICO_H_ */