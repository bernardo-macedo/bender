/*
 * Lifebar.h
 *
 *  Created on: Jun 12, 2015
 *      Author: -Bernardo
 */

#ifndef LIFEBAR_H_
#define LIFEBAR_H_

#include "Engine/GameObject.h"
#include "Engine/Sprite.h"

class Lifebar {
public:
	Lifebar(int posX, int posY, int scale, float maxLife);
	virtual ~Lifebar();

	void Render(float life);

private:
	Sprite* bar;
	Sprite* unit;
	int posX;
	int posY;
	float offsetX;
	float offsetY;
	float normalizationFactor;
};

#endif /* LIFEBAR_H_ */
