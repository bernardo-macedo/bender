/*
 * Enemy.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#include "Enemy.h"

#include <stdio.h>
#include <cwchar>
#include <string>

#include "EnemyStateBend.h"
#include "EnemyStateFollow.h"
#include "EnemyStatePatrolling.h"
#include "EnemyStatePunch.h"
#include "EnemyStateTakeDamage.h"
#include "Engine/Camera.h"
#include "Engine/Geometry/Point.h"
#include "Engine/Physics/Force.h"
#include "Engine/Physics/Physic.h"

#define ADD_STATE_EMPLACE(enemyStates, StateEnemy) this->enemyStatesMap.emplace(enemyStates, new StateEnemy(this))
#define ADD_STATE_INSERT(enemyStates, StateEnemy) this->enemyStatesMap.insert(std::make_pair<enemyStates, StateEnemy*>(enemyStates, new StateEnemy(this)));


Enemy::Enemy(int enemyScale, int x):
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

	box.SetX(x + 33*scale);
	box.SetY(ENEMY_MAP_GROUND*scale);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	spawnX = x;

	b = new Body("enemy", box.GetX(), box.GetY());

	b->ApplyForce(new Force("gravity", 0, 900));
	b->SetSpeedLimit(1000);

	flipped = false;
	fallUpdateCount = 0;
	isDead = false;
	isDamage = false;
	isTakingDamage = false;
	closeToBaon = false;
	bendCoolDown = 0;

	punchhit = new Sound("audio/sfx_char_punch_hit1.wav");
	kickhit = new Sound("audio/sfx_char_kick_hit1.wav");
	hp = 2;

	this->currentState->enter();
}

void Enemy::Update(float dt) {
	bendCoolDown -= dt;

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

void Enemy::Render() {
	if(!isDead){
		sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, flipped);
	}
}

void Enemy::NotifyCollision(GameObject* other) {
	if(other->GetID() == 100){
		if(other->GetBox().GetX() > box.GetX()){
			collisionFromRight = false;
		}
		if(other->GetBox().GetX() > box.GetX()){
			collisionFromRight = true;
		}
		isTakingDamage = true;
	}
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
	/*
	for(std::map<enemyStates, StateEnemy*>::iterator itr = enemyStatesMap.begin(); itr != enemyStatesMap.end(); itr++){
		delete itr->second;
	}
	delete sp;
	delete currentState;
	*/
}

void Enemy::TakeDamage(bool damage) {
	hp--;
	if(hp <= 0){
		isDead = true;
	}
	punchhit->Play(0);
}

bool Enemy::IsTakingDamage() {
	return isTakingDamage;
}

bool Enemy::IsRemovable() {
	return isRemovable;
}

bool Enemy::IsCloseToBaon() {
	return closeToBaon;
}

void Enemy::SetCloseToBaon(bool close) {
	closeToBaon = close;
}

bool Enemy::GetFlipped() {
	return flipped;
}

float Enemy::GetCoolDown() {
	return bendCoolDown;
}

void Enemy::SetCoolDown(float coolDown) {
	this->bendCoolDown = coolDown;
}

int Enemy::GetSpawnX() {
	return spawnX;
}

bool Enemy::IsCollisionFromRight() {
	return collisionFromRight;
}

void Enemy::SetTakingDamage(bool damage) {
	isTakingDamage = damage;
}

void Enemy::InitializeStates(){
	// Initialize all the states in Enemy here.
	ADD_STATE_EMPLACE(PATROLLING,   EnemyStatePatrolling);
	ADD_STATE_EMPLACE(FOLLOW,   	EnemyStateFollow);
	ADD_STATE_EMPLACE(PUNCH,        EnemyStatePunch);
	ADD_STATE_EMPLACE(BEND, 		EnemyStateBend);
	ADD_STATE_EMPLACE(TAKINGHIT, 		EnemyStateTakeDamage);
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
