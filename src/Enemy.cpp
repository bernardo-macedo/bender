/*
 * Enemy.cpp
 *
 *  Created on: 26/05/2015
 *      Author: Simiao
 */

#include "Enemy.h"

#include <map>
#include <string>

#include "enemystates/BenderEnemyBeingPushed.h"
#include "enemystates/BenderEnemyStateBend.h"
#include "enemystates/BenderEnemyStateDying.h"
#include "enemystates/BenderEnemyStateFollow.h"
#include "enemystates/BenderEnemyStatePatrolling.h"
#include "enemystates/BenderEnemyStatePunch.h"
#include "enemystates/BenderEnemyStateStanding.h"
#include "enemystates/BenderEnemyStateTakeDamage.h"
#include "Engine/Collision.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Force.h"
#include "Engine/Physics/Physic.h"
#include "Engine/Sprite.h"
#include "Engine/Timer.h"
#include "SpikeStone.h"

//#define ADD_STATE_EMPLACE(enemyStates, StateEnemy) this->enemyStatesMap.emplace(enemyStates, new StateEnemy(this))

Enemy::Enemy(int enemyScale, int x) : AbstractEnemy(enemyScale, x, 2, 50, 130, 0.2) {
	SetID(GameObject::ENEMY);
	InitializeSprite();
	InitializeStates();
	InitializeForces();
	Initialize();
	this->currentState->enter();
}

Enemy::~Enemy() {
	delete kickhit;
	delete punchhit;
	delete rockHit;
	delete currentState;
}

void Enemy::changeState(const enemyStates state_) {
	this->currentState->exit();
	this->currentState = this->enemyStatesMap.at(state_);
	this->currentState->enter();
}

bool Enemy::IsState(const enemyStates state_) {
	return (this->currentState == this->enemyStatesMap.at(state_));
}

bool Enemy::StateEnd() {
	return currentState->AskEnd();
}

void Enemy::Update(float dt) {
	bendCoolDown -= dt;

	if(!isDead) {
		currentState->update(dt);
		if(currentState->AskEnd()){
			if(IsState(BEINGPUSHED)){
				isTakingDamage = true;
			}
			changeState(Enemy::PATROLLING);
		}
		t->Update(dt);
		Physic::GetInstance()->UpdatePhysic(b, dt);
	} else {
		isRemovable = true;
	}


	box.SetX(b->GetX());
	box.SetY(b->GetY());
}

void Enemy::NotifyCollision(GameObject* other) {
	if(other->GetID() == GameObject::PEDRA_BASICO_BAON){
		if(other->GetBox().GetX() < box.GetX()){
			collisionFromRight = false;
		}
		if(other->GetBox().GetX() > box.GetX()){
			collisionFromRight = true;
		}
		isTakingDamage = true;
	}

	if(other->GetID() == GameObject::SPIKE_STONE_BAON){
		SpikeStone *pedra = (SpikeStone*)other;
		if(!IsState(Enemy::BEINGPUSHED)
				&& !IsState(Enemy::TAKINGHIT)
				&& !IsState(Enemy::DYING)){
			if(pedra->GetFlipped()){
				collisionFromRight = true;
			}
			else{
				collisionFromRight = false;
			}
			changeState(Enemy::BEINGPUSHED);
		}
	}
	if(other->GetID() == GameObject::PEDRA_DEFESA){
		if(!IsState(Enemy::STAND)){
			changeState(Enemy::STAND);
		}
	}

}

void Enemy::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {}

bool Enemy::Is(std::string type) {
	return AbstractEnemy::Is(type) || type.compare("BenderEnemy") == 0;
}

float Enemy::GetCoolDown() {
	return bendCoolDown;
}

void Enemy::SetCoolDown(float coolDown) {
	this->bendCoolDown = coolDown;
}

void Enemy::InitializeStates(){
	// Initialize all the states in Enemy here.
	this->enemyStatesMap.emplace(PATROLLING, new EnemyStatePatrolling(this));
	this->enemyStatesMap.emplace(FOLLOW, new EnemyStateFollow(this));
	this->enemyStatesMap.emplace(PUNCH, new EnemyStatePunch(this));
	this->enemyStatesMap.emplace(BEND, new EnemyStateBend(this));
	this->enemyStatesMap.emplace(TAKINGHIT, new EnemyStateTakeDamage(this));
	this->enemyStatesMap.emplace(DYING, new EnemyStateDying(this));
	this->enemyStatesMap.emplace(BEINGPUSHED, new EnemyBeingPushed(this));
	this->enemyStatesMap.emplace(STAND, new BenderEnemyStateStanding(this));


	currentState = enemyStatesMap.at(PATROLLING);
}

void Enemy::InitializeSprite() {
	LoadSpriteData("data/inimigo-data.txt");

	sp = new Sprite("img/Inimigo.png", 1, 0.1);

	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);

	box.SetX(spawnX + 33*scale);
	box.SetY(ENEMY_MAP_GROUND * scale);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
}

void Enemy::InitializeForces() {
	b = new Body("enemy", box.GetX(), box.GetY());

	b->ApplyForce(new Force("gravity", 0, 900));
	b->SetSpeedLimit(1000);
}

void Enemy::Initialize() {
	closeToBaon = false;
	bendCoolDown = 0;

	punchhit = new Sound("audio/sfx_char_punch_hit1.wav");
	kickhit = new Sound("audio/sfx_char_kick_hit1.wav");
	rockHit = new Sound("audio/sfx_throwRock_hit.wav");
}

void Enemy::SetWalkSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[WALK*3]);
		sp->SetFrameWidth(spriteData[WALK*3 + 1]);
		sp->SetFrameCount(spriteData[WALK*3 + 2]);
		sp->SetLine(WALK, spriteData[0]);
	}
}

void Enemy::SetStandSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[STAND*3]);
		sp->SetFrameWidth(spriteData[STAND*3 + 1]);
		sp->SetFrameCount(1);
		sp->SetLine(STAND, spriteData[0]);
	}
}

void Enemy::SetJumpSprite() {}

void Enemy::SetTakingDamageSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[TAKINGHIT*3]);
		sp->SetFrameWidth(spriteData[TAKINGHIT*3 + 1]);
		sp->SetFrameCount(spriteData[TAKINGHIT*3 + 2]);
		sp->SetLine(TAKINGHIT, spriteData[0]);
	}
}

void Enemy::SetDyingSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[DYING*3]);
		sp->SetFrameWidth(spriteData[DYING*3 + 1]);
		sp->SetFrameCount(spriteData[DYING*3 + 2]);
		sp->SetLine(DYING, spriteData[0]);
	}
}
