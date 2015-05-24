/*
 * Penguins.cpp
 *
 *  Created on: 12/05/2015
 *      Author: Pedro2
 */

#include "Penguins.h"

#include <math.h>

#include "Engine/Bullet.h"
#include "Engine/Camera.h"
#include "Engine/Game.h"
#include "Engine/InputManager.h"
#include "Engine/Physics/Physic.h"
#include "Engine/State.h"
#include "Engine/StillAnimation.h"

Penguins* Penguins::player;

Penguins::Penguins(float x, float y) {
	bodySP = new Sprite("img/penguin.png");
	cannonSP = new Sprite("img/cubngun.png");
	box.SetX(x);
	box.SetY(y);
	box.SetH(bodySP->GetHeight());
	box.SetW(bodySP->GetWidth());
	body = new Body("player", x, y);
	player = this;
	body->SetSpeedLimit(500);
	body->SetResistance(1.05);
	hp = 5;
	id = 0;
	cannonAngle = 0;
	linearSpeed = 0;
	explosion = new Sound("audio/boom.wav");
}

Penguins::~Penguins() {
	// TODO Auto-generated destructor stub
}

void Penguins::Update(float dt) {
	float accel = 1000;
	float mouseX = InputManager::GetInstance().GetMouseX();
	float mouseY = InputManager::GetInstance().GetMouseY();
	if(InputManager::GetInstance().IsKeyDown(W_KEY)){
		body->SetAccelX(accel*cos(body->GetRotation()*M_PI/180));
		body->SetAccelY(accel*sin(body->GetRotation()*M_PI/180));
	}
	if(InputManager::GetInstance().IsKeyDown(S_KEY)){
		body->SetAccelX(-accel*cos(body->GetRotation()*M_PI/180));
		body->SetAccelY(-accel*sin(body->GetRotation()*M_PI/180));
	}
	if(InputManager::GetInstance().KeyPress(A_KEY)){
		body->SetAngularVel(-300);
	}
	if(InputManager::GetInstance().KeyPress(D_KEY)){
		body->SetAngularVel(300);
	}
	if(InputManager::GetInstance().KeyRelease(A_KEY)){
			body->SetAngularVel(0);
	}
	if(InputManager::GetInstance().KeyRelease(D_KEY)){
		body->SetAngularVel(0);
	}
	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
		Shoot();
	}
	Physic::GetInstance()->UpdatePhysic(body, dt);
	cannonAngle = atan2((mouseY - Camera::pos.getY()) - box.GetY(), (mouseX - Camera::pos.getX()) - box.GetX());
	box.SetX(body->GetX());
	box.SetY(body->GetY());
	rotation = body->GetRotation();
	if(GetBox().GetX() <= 0){
		GetBox().SetX(1);
		body->SetVelX(-body->GetVelX());
	}
	if(GetBox().GetX() >= 1408){
		GetBox().SetX(1407);
		body->SetVelX(-body->GetVelX());
	}
	if(GetBox().GetY() <= 0){
			GetBox().SetY(1);
			body->SetVelY(-body->GetVelY());
	}
	if(GetBox().GetY() >= 1280){
		GetBox().SetY(1279);
		body->SetVelY(-body->GetVelY());
	}
}

void Penguins::Render() {
	bodySP->Render(box.GetX() - box.GetW()/2 + Camera::pos.getX(), box.GetY() - box.GetH()/2 + Camera::pos.getY(), body->GetRotation());
	cannonSP->Render(box.GetX() - box.GetW()/2 + Camera::pos.getX(), box.GetY() - box.GetH()/2 + Camera::pos.getY(), cannonAngle*180/M_PI);
}

bool Penguins::IsDead() {
	return hp <= 0;
}

bool Penguins::Is(std::string type) {
	return (type.compare("Penguins") == 0);
}

void Penguins::NotifyCollision(GameObject* other) {
	if(other->Is("Bullet")){
		Bullet *b = (Bullet*)other;
		if(b->targetsPlayer){
			hp -= 1;
			if(IsDead()){
				Sprite *sp = new Sprite("img/penguindeath.png", 5, 0.08);
				StillAnimation *st = new StillAnimation(GetBox().GetX(), GetBox().GetY(), 0, sp, 5*0.08, true);
				Game::GetInstance()->GetCurrentState()->AddObject(st);
				Camera::Follow(st);
				explosion->Play(0);
			}
			b->NotifyCollision(this);
		}
	}
}

void Penguins::Shoot() {
	Bullet *b = new Bullet(box.GetX(), box.GetY(), cannonAngle, 300, 300, "img/penguinbullet.png", false);
	Game::GetInstance()->GetCurrentState()->AddObject(b);
}
