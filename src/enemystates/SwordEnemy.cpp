/*
 * SwordEnemy.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemy.h"

#include <stdio.h>
#include <cwchar>

#include "../Engine/Geometry/Point.h"
#include "../Engine/Physics/Body.h"
#include "../Engine/Physics/Force.h"
#include "SwordEnemyPatrolling.h"

#define ADD_STATE_EMPLACE(enemyStates, StateEnemy) this->enemyStatesMap.emplace(enemyStates, new StateEnemy(this))
#define ADD_STATE_INSERT(enemyStates, StateEnemy) this->enemyStatesMap.insert(std::make_pair<enemyStates, StateEnemy*>(enemyStates, new StateEnemy(this)));

SwordEnemy::SwordEnemy(int enemyScale, int x) : WALK_SPEED_E(50) {
	LoadSpriteData();
	scale = enemyScale;
	flipped = false;

	sp = new Sprite("img/inimigo1.png", 1, 0.1);
	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);

	box.SetX(x + 33 * scale);
	box.SetY(ENEMY_MAP_GROUND * scale);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());

	b = new Body("enemy", box.GetX(), box.GetY());
	b->ApplyForce(new Force("gravity", 0, 900));
	b->SetSpeedLimit(1000);

	hp = 2;

	InitializeStates();

	t = new Timer();

	currentState = enemyStatesMap.at(PATROLLING);
	this->currentState->enter();
}

SwordEnemy::~SwordEnemy() {
	delete sp;
	delete currentState;
}

void SwordEnemy::Update(float dt) {
	if(!isDead) {
		currentState->update(dt);
		t->Update(dt);
		Physic::GetInstance()->UpdatePhysic(b, dt);
	} else {
		isRemovable = true;
	}


	box.SetX(b->GetX());
	box.SetY(b->GetY());
}

void SwordEnemy::Render() {
	if(!isDead){
		sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, flipped);
	}
}

void SwordEnemy::NotifyCollision(GameObject* other) {
}

void SwordEnemy::NotifyTileCollision() {
}

bool SwordEnemy::IsDead() {
	return hp <= 0;
}

bool SwordEnemy::IsRemovable() {
	return isRemovable;
}

bool SwordEnemy::Is(std::string type) {
	return type.compare("SwordEnemy") == 0;
}

bool SwordEnemy::GetFlipped() {
	return flipped;
}

void SwordEnemy::Stand() {
	sp->SetFrameHeight(spriteData[STAND * 3]);
	sp->SetFrameWidth(spriteData[STAND * 3 + 1]);
	sp->SetFrameCount(2);
	sp->SetLine(STAND, spriteData[0]);
	b->SetVelX(0);
}

void SwordEnemy::Walk() {
	sp->SetFrameHeight(spriteData[WALK * 3]);
	sp->SetFrameWidth(spriteData[WALK * 3 + 1]);
	sp->SetFrameCount(spriteData[WALK * 3 + 2]);
	sp->SetLine(WALK, spriteData[0]);
	if(!flipped){
		this->flipped = false;
		b->SetVelX(WALK_SPEED_E);
	}
	else{
		this->flipped = true;
		b->SetVelX(-WALK_SPEED_E);
	}
	t->Restart();
}

void SwordEnemy::Attack() {
	sp->SetFrameHeight(spriteData[ATTACK * 3]);
	sp->SetFrameWidth(spriteData[ATTACK * 3 + 1]);
	sp->SetFrameCount(spriteData[ATTACK * 3 + 2]);
	sp->SetLine(ATTACK, spriteData[0]);

	// do attack
}

void SwordEnemy::TakeDamage() {
	sp->SetFrameHeight(spriteData[TAKEDAMAGE * 3]);
	sp->SetFrameWidth(spriteData[TAKEDAMAGE * 3 + 1]);
	sp->SetFrameCount(spriteData[TAKEDAMAGE * 3 + 2]);
	sp->SetLine(TAKEDAMAGE, spriteData[0]);

	hp--;
	if(hp <= 0){
		isDead = true;
	}
}

void SwordEnemy::Die() {
	sp->SetFrameHeight(spriteData[DYING * 3]);
	sp->SetFrameWidth(spriteData[DYING * 3 + 1]);
	sp->SetFrameCount(spriteData[DYING * 3 + 2]);
	sp->SetLine(DYING, spriteData[0]);
}

void SwordEnemy::LoadSpriteData() {
	FILE *fp = fopen("data/inimigo1-data.txt", "r");
	fscanf(fp, "%d", &numEst);

	int val;
	while(!feof(fp)){
		fscanf(fp, "%d", &val);
		spriteData.push_back(val);
	}
	fclose(fp);
}

void SwordEnemy::ChangeState(const enemyStates state_) {
	this->currentState->exit();
	this->currentState = this->enemyStatesMap.at(state_);
	this->currentState->enter();
}

bool SwordEnemy::IsState(const enemyStates state_) {
	return (this->currentState == this->enemyStatesMap.at(state_));
}

bool SwordEnemy::StateEnd() {
	return currentState->AskEnd();
}

Sprite* SwordEnemy::GetSprite() {
	return sp;
}

void SwordEnemy::InitializeStates() {
	ADD_STATE_EMPLACE(PATROLLING,   SwordEnemyPatrolling);
}
