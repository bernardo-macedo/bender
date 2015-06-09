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

int Baon::WALK_SPEED = 50;
int Baon::RUN_SPEED  = 160;
int Baon::JUMP_SPEED = -166;
float Baon::DOUBLECLICK_TIME = 0.2;

Baon::Baon(int playerScale, float mapMax) {
	LoadSpriteData();

	scale = playerScale;
	Baon::WALK_SPEED = Baon::WALK_SPEED*scale;
	Baon::JUMP_SPEED = Baon::JUMP_SPEED*scale;
	Baon::RUN_SPEED = Baon::RUN_SPEED*scale;
	flipped = false;
	fallUpdateCount = 2;
	isDamage = false;

	// Cheats
	superJump = false;
	superSpeed = false;

	t = new Timer();
	stateManager = new BaonStateManager(this);
	runStates = NONE;

	sp = new Sprite("img/baon.png", 1, 0.1);
	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);
	sp->SetScaleX(playerScale);
	sp->SetScaleY(playerScale);

	box.SetX(Game::SCREEN_WIDTH/2);
	box.SetY(200);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());

	limitX = mapMax - (box.GetW() * scale);
	cameraLimitX = mapMax - Game::SCREEN_WIDTH/2;

	b = new Body("baon", box.GetX(), box.GetY());
	b->ApplyForce(new Force("gravity", 0, 900));
	isDead = false;

}

Baon::~Baon() {
	delete sp;
	delete t;
	delete stateManager;
}

Sprite* Baon::GetSprite() {
	return sp;
}

void Baon::TakeDamage() {
	isDead = true;
}

void Baon::LoadSpriteData() {
	FILE *fp = fopen("data/baon-data.txt", "r");
	fscanf(fp, "%d", &numEst);
	int val;
	while(!feof(fp)){
		fscanf(fp, "%d", &val);
		spriteData.push_back(val);
	}
}

void Baon::Update(float dt) {
	stateManager->Update(dt);
	if(!stateManager->GetCurrentState()->Is("JUMPING")
			&& !stateManager->GetCurrentState()->Is("FALLING")){
		sp->Update(dt);
	}
	Physic::GetInstance()->UpdatePhysic(b, dt);
	box.SetX(b->GetX());
	box.SetY(b->GetY());

	if(box.GetX() <= Game::SCREEN_WIDTH/2 || box.GetX() >= cameraLimitX){
		Camera::Unfollow();
	} else if(box.GetX() > Game::SCREEN_WIDTH/2){
		Camera::Follow(this);
	}

	// Impede o player a sair do mapa pela esquerda
	if (box.GetX() < 0) {
		box.SetX(0);
		b->SetAccelX(0);
		b->SetVelX(0);
		b->SetX(0);
	}

	// Impede o player a sair do mapa pela direita
	if (box.GetX() > limitX) {
		box.SetX(limitX );
		b->SetAccelX(0);
		b->SetVelX(0);
		b->SetX(limitX);
	}

	// Cheats
	if (InputManager::GetInstance().KeyPress(O_KEY)) {
		SetSuperJump(!superJump);
	}
	if (InputManager::GetInstance().KeyPress(P_KEY)) {
		SetSuperSpeed(!superSpeed);
	}
}

void Baon::Render() {
	sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, stateManager->GetCurrentState()->IsFlipped());
}

void Baon::NotifyCollision(GameObject* other) {
}

bool Baon::IsDead() {
	// TODO: hitpoints
	return isDead;
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
		if (superSpeed) {
			b->SetVelX(4 * RUN_SPEED);
		} else {
			b->SetVelX(RUN_SPEED);
		}
	}
	else{
		this->flipped = true;
		if (superSpeed) {
			b->SetVelX(4 * -RUN_SPEED);
		} else {
			b->SetVelX(-RUN_SPEED);
		}

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
	b->SetAccelX(0);
}

void Baon::Jump(bool flipped) {
	sp->SetFrameHeight(spriteData[JUMP*3]);
	sp->SetFrameWidth(spriteData[JUMP*3 + 1]);
	sp->SetFrameCount(spriteData[JUMP*3 + 2]);
	sp->SetLine(JUMP, spriteData[0]);

	if (superJump) {
		b->SetVelY(4 * JUMP_SPEED );
	} else {
		b->SetVelY(JUMP_SPEED);
	}
}
void Baon::Fall() {
	if(fallUpdateCount < 5){
		sp->SetFrame(fallUpdateCount);
		fallUpdateCount++;
	}
}

void Baon::Punch(){
	sp->SetFrameHeight(spriteData[6*3]);
	sp->SetFrameWidth(spriteData[6*3 + 1]);
	sp->SetFrameCount(spriteData[6*3 + 2]);
	sp->SetLine(6, spriteData[0]);
	b->SetVelX(0);
}

void Baon::Kick(){
	sp->SetFrameHeight(spriteData[7*3]);
	sp->SetFrameWidth(spriteData[7*3 + 1]);
	sp->SetFrameCount(spriteData[7*3 + 2]);
	sp->SetLine(7, spriteData[0]);
	b->SetVelX(0);
}
void Baon::MidAir(){
	if (b->GetForce("gravity") == NULL) {
		b->ApplyForce(new Force("gravity", 0, 1200));
	}
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

void Baon::NotifyTileCollision() {
	stateManager->GetCurrentState()->NotifyTileCollision();
}

BaonStateManager* Baon::GetState(){
	return stateManager;
}

// Cheats
void Baon::SetSuperJump(bool superJump) {
	this->superJump = superJump;
}

void Baon::SetSuperSpeed(bool superSpeed) {
	this->superSpeed = superSpeed;
}

bool Baon::GetSuperJump() {
	return superJump;
}

bool Baon::GetSuperSpeed() {
	return superSpeed;
}
