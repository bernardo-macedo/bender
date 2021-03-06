/*
 * Face.cpp
 *
 *  Created on: 19/03/2015
 *      Author: Pedro
 */

#include "Face.h"
#include <cstdlib>
#include <math.h>
#include "Constants.h"

Face::Face(int x, int y) {
	int newX, newY, angle;

	angle = (rand() % 360);
	newX = x + 200*cos(angle);
	newY = y + 200*sin(angle);


	sp = new Sprite(Constants::ImgPath + "penguinface.png");
	box.SetX(newX - sp->GetWidth()/2);
	box.SetY(newY - sp->GetHeight()/2);
	box.SetW(sp->GetWidth());
	box.SetH(sp->GetHeight());
	hitPoints = 30;
}

Face::~Face() {
	// TODO Auto-generated destructor stub
}

void Face::Damage(int damage) {
	hitPoints -= damage;
}

void Face::Update() {
}

void Face::Render(int cameraX, int cameraY) {
	sp->Render(GetBox().GetX() + cameraX, GetBox().GetY() + cameraY);
}

bool Face::IsDead() {
	if(hitPoints <= 0){
		return true;
	}
	return false;
}
