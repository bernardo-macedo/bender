/*
 * Baon.cpp
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#include "Baon.h"

#include <stdio.h>
#include <cwchar>
#include <string>

#include "baonstates/BaonState.h"
#include "baonstates/BaonStateManager.h"
#include "Engine/Camera.h"
#include "Engine/Game.h"
#include "Engine/Geometry/Point.h"
#include "Engine/InputManager.h"
#include "Engine/Physics/Force.h"
#include "Engine/Physics/Physic.h"

int Baon::WALK_SPEED = 150;
int Baon::RUN_SPEED  = 500;
float Baon::DOUBLECLICK_TIME = 0.2;

Baon::Baon() {
	FILE *fp = fopen("data/baon-data.txt", "r");
	fscanf(fp, "%d", &numEst);

	int val;
	while(!feof(fp)){
		fscanf(fp, "%d", &val);
		spriteData.push_back(val);
	}
	t = new Timer();
	stateManager = new BaonStateManager();
    //----------------------------------------
	state = STAND;
	sp = new Sprite("img/baon.png", 1, 0.1);
	runStates = NONE;

	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);

	box.SetX(Game::SCREEN_WIDTH/2);
	box.SetY(MAP_GROUND);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());
	sp->SetScaleX(3);
	sp->SetScaleY(3);

	b = new Body("baon", box.GetX(), box.GetY());

	flipped = false;
	fallUpdateCount = 2;
}

void Baon::Update(float dt) {
	stateManager->Update(this, dt);
	if(!stateManager->GetCurrentState()->Is("JUMPING")
			&& !stateManager->GetCurrentState()->Is("FALLING")){
		sp->Update(dt);
	}
	Physic::GetInstance()->UpdatePhysic(b, dt);
	box.SetX(b->GetX());
	box.SetY(b->GetY());

	if(box.GetX() <= 512 || box.GetX() >= 17485){
		Camera::Unfollow();
	} else if(box.GetX() > 512){
		Camera::Follow(this);
	}
}

void Baon::Render() {
	//sp->Render(box.GetX() -  box.GetW()/2 - Camera::pos.getX(), box.GetY() - box.GetH()/2 - Camera::pos.getY(), 0, flipped);
	sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, stateManager->GetCurrentState()->IsFlipped());
}

void Baon::NotifyCollision(GameObject* other) {
}

bool Baon::IsDead() {
	return false;
}

bool Baon::Is(std::string type) {
	return type.compare("Baon") == 0;
}

//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------


//--------------------------------------------------------
//--------------------------------------------------------
void Baon::Run(bool flipped) {
	sp->SetFrameHeight(spriteData[RUN*3]);
	sp->SetFrameWidth(spriteData[RUN*3 + 1]);
	sp->SetFrameCount(spriteData[RUN*3 + 2]);
	sp->SetLine(RUN, spriteData[0]);
	if(!flipped){
		this->flipped = false;
		b->SetVelX(RUN_SPEED);
	}
	else{
		this->flipped = true;
		b->SetVelX(-RUN_SPEED);
	}
}

void Baon::Walk(bool flipped) {
	sp->SetFrameHeight(spriteData[WALK*3]);
	sp->SetFrameWidth(spriteData[WALK*3 + 1]);
	sp->SetFrameCount(spriteData[WALK*3 + 2]);
	sp->SetLine(WALK, spriteData[0]);
	if(!flipped){
		this->flipped = false;
		b->SetVelX(WALK_SPEED);
	}
	else{
		this->flipped = true;
		b->SetVelX(-WALK_SPEED);
	}
	t->Restart();

	state = WALK;
}

void Baon::Stand(bool flipped) {
	sp->SetFrameHeight(spriteData[STAND*3]);
	sp->SetFrameWidth(spriteData[STAND*3 + 1]);
	sp->SetFrameCount(1);
	sp->SetLine(STAND, spriteData[0]);
	b->SetVelX(0);
}

void Baon::Jump(bool flipped) {
	sp->SetFrameHeight(spriteData[JUMP*3]);
	sp->SetFrameWidth(spriteData[JUMP*3 + 1]);
	sp->SetFrameCount(spriteData[JUMP*3 + 2]);
	sp->SetLine(JUMP, spriteData[0]);

	b->SetVelY(-500);
	b->ApplyForce(new Force("gravity", 0, 900));
}
void Baon::Fall() {
	if(fallUpdateCount < 5){
		sp->SetFrame(fallUpdateCount);
		fallUpdateCount++;
	}
}

void Baon::MidAir(){
	if(InputManager::GetInstance().KeyPress(A_KEY)){
		if(stateManager->GetPreviousState()->Is("WALK")
				|| stateManager->GetPreviousState()->Is("STAND")){
			b->SetVelX(-WALK_SPEED);
			stateManager->GetCurrentState()->SetFlipped(true);
		}
		else{
			b->SetVelX(-RUN_SPEED);
			stateManager->GetCurrentState()->SetFlipped(true);
		}
	}
	else{
		if(InputManager::GetInstance().KeyPress(D_KEY)){
			if(stateManager->GetPreviousState()->Is("WALK")
					|| stateManager->GetPreviousState()->Is("STAND")){
				b->SetVelX(WALK_SPEED);
				stateManager->GetCurrentState()->SetFlipped(false);
			}
			else{
				b->SetVelX(RUN_SPEED);
				stateManager->GetCurrentState()->SetFlipped(false);
			}
		}
	}
	if(InputManager::GetInstance().KeyRelease(A_KEY)){
		b->SetVelX(0);
	}
	else{
		if(InputManager::GetInstance().KeyRelease(D_KEY)){
			b->SetVelX(0);
		}
	}
}
Body* Baon::GetBody() {
	return b;
}
