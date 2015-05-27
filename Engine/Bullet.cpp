/*
 * Bullet.cpp
 *
 *  Created on: 01/05/2015
 *      Author: Pedro2
 */

#include "Bullet.h"
#include "Camera.h"

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance,
		std::string sprite, bool targetsPlayer) {
	sp = new Sprite(sprite, 4, 0.08);
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	box.SetX(x);
	box.SetY(y);
	distanceLeft = maxDistance;
	this->speed.setX(cos(angle)*speed);
	this->speed.setY(sin(angle)*speed);
	rotation = angle*180/M_PI;
	this->targetsPlayer = targetsPlayer;
}

void Bullet::Update(float dt) {
	sp->Update(dt);
	box.SetX(box.GetX() + speed.getX()*dt);
	box.SetY(box.GetY() + speed.getY()*dt);
	distanceLeft -= sqrt(pow(speed.getX()*dt, 2) + pow(speed.getY()*dt, 2));
}

void Bullet::Render() {
	sp->Render(box.GetX() - box.GetW()/2 + Camera::pos.getX(), box.GetY() - box.GetH()/2 + Camera::pos.getY(), rotation);
}

bool Bullet::IsDead() {
	return distanceLeft <= 0;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::NotifyCollision(GameObject* other) {
	if((other->Is("Alien") && !targetsPlayer)
			|| (other->Is("Penguins") && targetsPlayer)){
		distanceLeft = 0;
	}
}

bool Bullet::Is(std::string type) {
	return (type.compare("Bullet") == 0);
}
