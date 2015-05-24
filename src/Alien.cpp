/*
 * Alien.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Pedro
 */

#include "Alien.h"

#include <math.h>
#include <string>

#include "Engine/Bullet.h"
#include "Engine/Camera.h"
#include "Engine/Game.h"
#include "Engine/InputManager.h"
#include "Engine/State.h"
#include "Engine/StillAnimation.h"
#include "Penguins.h"

#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define PI 3.14

Alien::Alien(float x, float y, int nMinions, int id) {
	this->id = id;
	rotation = 0;
	sp = new Sprite("img/alien.png");
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	box.SetX(x);
	box.SetY(y);
	float lastPos = 0;
	for(int i = 0; i < nMinions; i++){
		minionArray.push_back(new Minion(this, lastPos));
		lastPos += ((360.0*PI)/180)/(float)nMinions;
	}
	hp = 6;
	explosion  = new Sound("audio/boom.wav");
	alienState = RESTING;
	shootCoolDown = new Timer();
}

Alien::~Alien() {
}

void Alien::Update(float dt) {
	int indNext = 0;

	if(alienState == RESTING){
		shootCoolDown->Update(dt);
		if(shootCoolDown->Get() > 1){
			Action a(Action::ActionType::MOVE, Penguins::player->GetBox().GetX(), Penguins::player->GetBox().GetY());
			taskQueue.push(a);
			alienState = MOVING;
		}
	}

	if(alienState == MOVING){
		Action a = taskQueue.front();
		float dx = a.pos->getX() - box.GetX();
		float dy = a.pos->getY() - box.GetY();

		float mod = sqrt(dx*dx + dy*dy);
		float velx, vely;
		if(mod > 0){
			velx = (dx/mod)*500;
			vely = (dy/mod)*500;
		}
		else{
			velx = 0;
			vely = 0;
		}

		if(fabs(velx*dt) >= fabs(dx) && fabs(vely*dt) >= fabs(dy)){
			box.SetX(a.pos->getX());
			box.SetY(a.pos->getY());
			taskQueue.pop();
			float distOldX = minionArray[indNext]->GetBox().GetX() - Penguins::player->GetBox().GetX();
			float distOldY = minionArray[indNext]->GetBox().GetY() - Penguins::player->GetBox().GetY();
			float distOld = sqrt(pow(distOldX, 2) + pow(distOldY,2));
			for(unsigned i = 1; i < minionArray.size(); i++){
				float distNewX = minionArray[i]->GetBox().GetX() - Penguins::player->GetBox().GetX();
				float distNewY = minionArray[i]->GetBox().GetY() - Penguins::player->GetBox().GetY();
				float distNew = sqrt(pow(distNewX, 2) + pow(distNewY,2));
				if(distNew < distOld){
					indNext = i;
					distOld = distNew;
				}
			}
			Point p;
			p.setX(Penguins::player->GetBox().GetX());
			p.setY(Penguins::player->GetBox().GetY());
			minionArray[indNext]->Shoot(p);
			alienState = RESTING;
			shootCoolDown->Restart();
		}
		else{
			box.SetX(box.GetX() + velx*dt);
			box.SetY(box.GetY() + vely*dt);
		}
	}


	for(unsigned i = 0; i < minionArray.size(); i++){
		Minion* m = (Minion*)minionArray[i];
		m->Update(dt);
	}
	rotation -= 1;
}

void Alien::Render() {
	for(unsigned i = 0; i < minionArray.size(); i++){
		Minion* m = (Minion*)minionArray[i];
		m->Render();
	}
	sp->Render((box.GetX() - box.GetW()/2) + Camera::pos.getX(), (box.GetY() - box.GetH()/2) + Camera::pos.getY(), rotation);
}

bool Alien::IsDead() {
	return hp <= 0;
}

bool Alien::Is(std::string type){
	return (type.compare("Alien") == 0);
}

void Alien::NotifyCollision(GameObject* other){
	if(other->Is("Bullet")){
		Bullet* b = (Bullet*)other;
		if(!b->targetsPlayer){
			other->NotifyCollision(this);
			hp -= 1;
			if(hp <= 0){
				explosion->Play(0);
				Sprite *spr = new Sprite("img/aliendeath.png", 4, 0.09);
				StillAnimation *still = new StillAnimation(box.GetX(),
															box.GetY(),
															0, spr,	4*0.09, true);
				Game::GetInstance()->GetCurrentState()->AddObject(still);
			}
		}
	}
}
