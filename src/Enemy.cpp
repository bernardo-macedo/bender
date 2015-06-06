/*
 * Enemy.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#include "Enemy.h"
#include "Engine/Camera.h"
#include "Engine/Game.h"
#include "Engine/InputManager.h"
#include "Engine/Physics/Physic.h"
#include "Engine/Physics/Force.h"
#include "Engine/Physics/Body.h"

#include "EnemyStatePunch.h"
#include "EnemyStatePatrolling.h"
#include "EnemyStateFollow.h"

#include <stdio.h>
#include <iostream>

#define ADD_STATE_EMPLACE(enemyStates, StateEnemy) this->enemyStatesMap.emplace(enemyStates, new StateEnemy(this))
#define ADD_STATE_INSERT(enemyStates, StateEnemy) this->enemyStatesMap.insert(std::make_pair<enemyStates, StateEnemy*>(enemyStates, new StateEnemy(this)));


Enemy::Enemy(int enemyScale):
	WALK_SPEED_E(50),
	RUN_SPEED_E(130),
	DOUBLECLICK_TIME(0.2)
	{
	FILE *fp = fopen("data/inimigo-data.txt", "r");
	fscanf(fp, "%d", &numEst);

	int val;
	while(!feof(fp)){
		fscanf(fp, "%d", &val);
		spriteData.push_back(val);
	}
	fclose(fp);
	scale = enemyScale;
	t = new Timer();
    //----------------------------------------

    InitializeStates();
    currentState = enemyStatesMap.at(PATROLLING);
	sp = new Sprite("img/Inimigo.png", 1, 0.1);
	runStates = NONE;

	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);

	box.SetX(Game::SCREEN_WIDTH/2 + 100);
	box.SetY(ENEMY_MAP_GROUND);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);

	b = new Body("enemy", box.GetX(), box.GetY());

	b->ApplyForce(new Force("gravity", 0, 900));
	b->SetSpeedLimit(1000);

	flipped = false;
	fallUpdateCount = 0;
	isDead = false;

	this->currentState->enter();

}

void Enemy::Update(float dt) {

	if(!isDead){
		currentState->update(dt);
		t->Update(dt);
		Physic::GetInstance()->UpdatePhysic(b, dt);
	}

	box.SetX(b->GetX());
	box.SetY(b->GetY());
}

void Enemy::Render() {
	if(!isDead){
		sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, flipped);
	}
}

void Enemy::NotifyCollision(GameObject* other) {
}

bool Enemy::IsDead() {
	return isDead;
}

bool Enemy::Is(std::string type) {
	return type.compare("Enemy") == 0;
}

//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------

void Enemy::Run(bool flipped) {
	if(!flipped){
		this->flipped = false;
		b->SetVelX(RUN_SPEED_E);
	}
	else{
		this->flipped = true;
		b->SetVelX(-RUN_SPEED_E);
	}

}

void Enemy::Walk(bool flipped) {
	sp->SetFrameHeight(spriteData[WALK*3]);
	sp->SetFrameWidth(spriteData[WALK*3 + 1]);
	sp->SetFrameCount(spriteData[WALK*3 + 2]);
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

void Enemy::Stand(bool flipped) {
	sp->SetFrameHeight(spriteData[STAND*3]);
	sp->SetFrameWidth(spriteData[STAND*3 + 1]);
	sp->SetFrameCount(1);
	sp->SetLine(STAND, spriteData[0]);
	b->SetVelX(0);

	runStates= NONE;

	if(flipped){
		runStates = PRERUNL;
	}
	else{
		runStates = PRERUNR;
	}

	fallUpdateCount = 0;

}

void Enemy::Jump(bool flipped) {
	sp->SetFrameHeight(spriteData[JUMP*3]);
	sp->SetFrameWidth(spriteData[JUMP*3 + 1]);
	sp->SetFrameCount(spriteData[JUMP*3 + 2]);
	sp->SetLine(JUMP, spriteData[0]);

	b->SetVelY(-500);
	b->ApplyForce(new Force("gravity", 0, 900));

}

void Enemy::NotifyTileCollision() {
	// TODO
}

Enemy::~Enemy() {
	for(std::map<enemyStates, StateEnemy*>::iterator itr = enemyStatesMap.begin(); itr != enemyStatesMap.end(); itr++){
		delete itr->second;
	}
	delete sp;
	delete currentState;
}

void Enemy::InitializeStates(){
	// Initialize all the states in Enemy here.
	ADD_STATE_EMPLACE(PATROLLING,   EnemyStatePatrolling);
	ADD_STATE_EMPLACE(FOLLOW,   	EnemyStateFollow);
	ADD_STATE_EMPLACE(PUNCH,        EnemyStatePunch);
}

void Enemy::changeState(const enemyStates state_){
	this->currentState->exit();
	this->currentState = this->enemyStatesMap.at(state_);
	this->currentState->enter();
}

bool Enemy::IsState(const enemyStates state_){
	if(this->currentState == this->enemyStatesMap.at(state_)){
		return true;
	}
	else{
		return false;
	}
}

Sprite* Enemy::GetSprite(){
	return sp;
}

Timer* Enemy::Time(){
	return t;
}

void Enemy::SetDead(bool isDead_){
	isDead = isDead_;
}

bool Enemy::StateEnd() {
	return currentState->AskEnd();
}
