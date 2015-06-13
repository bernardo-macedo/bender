/*
 * Lifebar.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: -Bernardo
 */

#include "Lifebar.h"

Lifebar::Lifebar(int posX, int posY, int scale, float maxLife) :
	posX(posX), posY(posY) {

	bar = new Sprite("img/lifebar.png");
	unit = new Sprite("img/lifeunit.png");

	bar->SetScaleX(scale);
	bar->SetScaleY(scale);

	unit->SetScaleY(scale);

	offsetX = 19 * scale;
	offsetY = 6 * scale;

	normalizationFactor = 9.1 * scale / maxLife;
}

Lifebar::~Lifebar() {
	delete bar;
	delete unit;
}

void Lifebar::Render(float life) {
	float normalizedLife = life * normalizationFactor;
	unit->SetScaleX(normalizedLife);

	bar->Render(posX, posY, 0);
	unit->Render(posX + offsetX , posY + offsetY, 0);
}
