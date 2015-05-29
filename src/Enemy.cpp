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

#include "EnemyStatePatrolling.h"
 #include "EnemyStateFollow.h"

#include <stdio.h>

#define ADD_STATE_EMPLACE(enemyStates, StateEnemy) this->enemyStatesMap.emplace(enemyStates, new StateEnemy(this))
#define ADD_STATE_INSERT(enemyStates, StateEnemy) this->enemyStatesMap.insert(std::make_pair<enemyStates, StateEnemy*>(enemyStates, new StateEnemy(this)));


Enemy::Enemy():
	WALK_SPEED_E(50),
	RUN_SPEED_E(50),
	DOUBLECLICK_TIME(0.2)
	{
	FILE *fp = fopen("data/baon-data.txt", "r");
	fscanf(fp, "%d", &numEst);

	int val;
	while(!feof(fp)){
		fscanf(fp, "%d", &val);
		spriteData.push_back(val);
	}
	fclose(fp);
	t = new Timer();
    //----------------------------------------

    InitializeStates();
    currentState = enemyStatesMap.at(PATROLLING);
	sp = new Sprite("img/baon.png", 1, 0.1);
	runStates = NONE;

	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);

	box.SetX(Game::SCREEN_WIDTH/2 + 100);
	box.SetY(ENEMY_MAP_GROUND);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());
	sp->SetScaleX(2);
	sp->SetScaleY(2);

	b = new Body("enemy", box.GetX(), box.GetY());
	b->SetSpeedLimit(1000);

	flipped = false;
	fallUpdateCount = 0;

	this->currentState->enter();

}

void Enemy::Update(float dt) {

	currentState->update(dt);

	t->Update(dt);
	//Physic::GetInstance()->UpdatePhysic(b, dt);

	sp->Update(dt);

	box.SetX(b->GetX());
	box.SetY(b->GetY());
}

void Enemy::Render() {
	//sp->Render(box.GetX() -  box.GetW()/2 - Camera::pos.getX(), box.GetY() - box.GetH()/2 - Camera::pos.getY(), 0, flipped);
	sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, flipped);
}

void Enemy::NotifyCollision(GameObject* other) {
}

bool Enemy::IsDead() {
	return false;
}

bool Enemy::Is(std::string type) {
	return type.compare("Enemy") == 0;
}

//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------

void Enemy::Run(bool flipped) {
	sp->SetFrameHeight(spriteData[RUN*3]);
	sp->SetFrameWidth(spriteData[RUN*3 + 1]);
	sp->SetFrameCount(spriteData[RUN*3 + 2]);
	sp->SetLine(RUN, spriteData[0]);
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

void Enemy::InitializeStates(){
	// Initialize all the states in Enemy here.
	ADD_STATE_EMPLACE(PATROLLING,   EnemyStatePatrolling);
	ADD_STATE_EMPLACE(FOLLOW,   	EnemyStateFollow);
}

void Enemy::changeState(const enemyStates state_){
	this->currentState->exit();
	this->currentState = this->enemyStatesMap.at(state_);
	this->currentState->enter();
}

Sprite* Enemy::getSprite(){
	return sp;
}

Timer* Enemy::Time(){
	return t;
}
