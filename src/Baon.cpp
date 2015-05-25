/*
 * Baon.cpp
 *
 *  Created on: 24/05/2015
 *      Author: Pedro2
 */

#include "Baon.h"
#include "Engine/Camera.h"
#include "Engine/Game.h"
#include "Engine/InputManager.h"
#include "Engine/Physics/Physic.h"
#include "Engine/Physics/Force.h"

#include <stdio.h>

int Baon::WALK_SPEED = 150;
int Baon::RUN_SPEED  = 300;
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
	sp->SetScaleX(2);
	sp->SetScaleY(2);

	b = new Body("baon", box.GetX(), box.GetY());
	b->SetSpeedLimit(1000);

	flipped = false;
	fallUpdateCount = 0;

}

void Baon::Update(float dt) {
	if(InputManager::GetInstance().KeyPress(D_KEY)){
		if(state != WALK && state != RUN && state != JUMP && state != FALLING){
			if(runStates == PRERUNR && t->Get() < DOUBLECLICK_TIME){
				Run(false);
			}
			else {
				Walk(false);
			}
		}
		else{
			if(state == JUMP || state == FALLING){
				flipped = false;
				b->SetVelX(WALK_SPEED);
			}
		}
	}
	if(InputManager::GetInstance().KeyPress(A_KEY)){
		if(state != WALK && state != RUN && state != JUMP && state != FALLING){
			if(runStates == PRERUNL && t->Get() < DOUBLECLICK_TIME){
				Run(true);
			}
			else{
				Walk(true);
			}
		}
		else{
			if(state == JUMP || state == FALLING){
				flipped = true;
				b->SetVelX(-WALK_SPEED);
			}
		}
	}
	if(InputManager::GetInstance().KeyRelease(A_KEY)){
		if(state != JUMP && state != FALLING){
			Stand(true);
		}
		else{
			b->SetVelX(0);
		}
	}
	if(InputManager::GetInstance().KeyRelease(D_KEY)){
		if(state != JUMP && state != FALLING){
			Stand(false);
		}
		else{
			b->SetVelX(0);
		}
	}
	if(InputManager::GetInstance().KeyPress(W_KEY)){
		if(state != JUMP && state != FALLING){
			Jump(flipped);
		}
	}

	//-----------------------------------------------------------
	//-----------------------------------------------------------

	if(state == FALLING){
		if(fallUpdateCount < 3){
			if(sp->Update(dt)){
				fallUpdateCount++;
			}
		}
		if(box.GetY() >= MAP_GROUND){
			box.SetY(MAP_GROUND);
			b->removeForce("gravity");
			b->SetVelY(0);
			if(InputManager::GetInstance().IsKeyDown(D_KEY)){
				Walk(false);
			}
			else{
				if(InputManager::GetInstance().IsKeyDown(A_KEY)){
					Walk(true);
				}
				else{
					Stand(flipped);
				}
			}
		}
	}
	if(state == JUMP){
		if(b->GetVelY() > 0){
			state = FALLING;
		}
	}

	t->Update(dt);
	Physic::GetInstance()->UpdatePhysic(b, dt);

	if(state != JUMP && state != FALLING){
		sp->Update(dt);
	}

	box.SetX(b->GetX());
	box.SetY(b->GetY());
}

void Baon::Render() {
	//sp->Render(box.GetX() -  box.GetW()/2 - Camera::pos.getX(), box.GetY() - box.GetH()/2 - Camera::pos.getY(), 0, flipped);
	sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, flipped);
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

	state = RUN;
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

	runStates= NONE;
	if(state == WALK){
		if(flipped){
			runStates = PRERUNL;
		}
		else{
			runStates = PRERUNR;
		}
	}
	fallUpdateCount = 0;
	state = STAND;
}

void Baon::Jump(bool flipped) {
	sp->SetFrameHeight(spriteData[JUMP*3]);
	sp->SetFrameWidth(spriteData[JUMP*3 + 1]);
	sp->SetFrameCount(spriteData[JUMP*3 + 2]);
	sp->SetLine(JUMP, spriteData[0]);

	b->SetVelY(-500);
	b->ApplyForce(new Force("gravity", 0, 900));

	state = JUMP;
}
