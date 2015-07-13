/*
 * BigEnemy.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: -Bernardo
 */

#include "BigEnemy.h"

#include "enemystates/BigEnemyBeingPunched.h"
#include "enemystates/BigEnemyStandingState.h"
#include "enemystates/BigEnemyStateAttacking.h"
#include "enemystates/BigEnemyStateDying.h"
#include "enemystates/BigEnemyStateFollow.h"
#include "enemystates/BigEnemyStatePatrolling.h"
#include "enemystates/BigEnemyStateTakeDamage.h"
#include "Engine/Collision.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Force.h"
#include "Engine/Physics/Physic.h"
#include "Engine/Sprite.h"
#include "SpikeStone.h"

BigEnemy::BigEnemy(int enemyScale, int x) : AbstractEnemy(enemyScale, x, 5, 30, 90, 0.2) {
	SetID(GameObject::BIG_ENEMY);
	InitializeSprite();
	InitializeStates();
	InitializeForces();
	Initialize();
	this->currentState->enter();
}

BigEnemy::~BigEnemy() {
	// TODO Auto-generated destructor stub
}

void BigEnemy::changeState(const enemyStates state_) {
	this->currentState->exit();
	this->currentState = this->enemyStatesMap.at(state_);
	this->currentState->enter();
}

bool BigEnemy::IsState(const enemyStates state_) {
	return (this->currentState == this->enemyStatesMap.at(state_));
}

bool BigEnemy::StateEnd() {
	return currentState->AskEnd();
}

void BigEnemy::Update(float dt) {
	collidedHorizontally = false;
	if(!isDead) {
		currentState->update(dt);
		if(currentState->AskEnd()){
			if(IsState(BEINGPUSHED)){
				isTakingDamage = true;
			}
			changeState(BigEnemy::PATROLLING);
		}
		Physic::GetInstance()->UpdatePhysic(b, dt);
	} else {
		isRemovable = true;
	}

	box.SetX(b->GetX());
	box.SetY(b->GetY());
}

void BigEnemy::NotifyCollision(GameObject* other) {
	if(other->GetID() == GameObject::PEDRA_BASICO_BAON){
		if(other->GetBox().GetX() > box.GetX()){
			collisionFromRight = false;
		}
		if(other->GetBox().GetX() > box.GetX()){
			collisionFromRight = true;
		}
		isTakingDamage = true;
	}
	if(other->GetID() == GameObject::SPIKE_STONE_BAON){
		SpikeStone *pedra = (SpikeStone*)other;
		if(!IsState(BigEnemy::BEINGPUSHED)
				&& !IsState(BigEnemy::TAKINGHIT)
				&& !IsState(BigEnemy::DYING)){
			if(pedra->GetFlipped()){
				collisionFromRight = true;
			}
			else{
				collisionFromRight = false;
			}
			changeState(BigEnemy::BEINGPUSHED);
		}
	}

	if(other->GetID() == GameObject::PEDRA_DEFESA){
		if(!IsState(BigEnemy::STAND)){
			changeState(BigEnemy::STAND);
		}
	}

	if(other->GetID() == GameObject::CONTROLE_BEND) {
		if(!IsState(BigEnemy::TAKINGHIT)){
			changeState(BigEnemy::TAKINGHIT);
		}
	}
}

void BigEnemy::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {
	if (collisionAxis == Collision::CollisionAxis::AXIS_X) {
		collidedHorizontally = true;
	}
}

bool BigEnemy::Is(std::string type) {
	return AbstractEnemy::Is(type) || type.compare("BigEnemy") == 0;
}

void BigEnemy::SetWalkSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[WALK*3]);
		sp->SetFrameWidth(spriteData[WALK*3 + 1]);
		sp->SetFrameCount(spriteData[WALK*3 + 2]);
		sp->SetLine(WALK, spriteData[0]);
	}
}

void BigEnemy::SetStandSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[STAND*3]);
		sp->SetFrameWidth(spriteData[STAND*3 + 1]);
		sp->SetFrameCount(1);
		sp->SetLine(STAND, spriteData[0]);
	}
}

void BigEnemy::SetJumpSprite() {}

void BigEnemy::SetTakingDamageSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[TAKINGHIT*3]);
		sp->SetFrameWidth(spriteData[TAKINGHIT*3 + 1]);
		sp->SetFrameCount(spriteData[TAKINGHIT*3 + 2]);
		sp->SetLine(TAKINGHIT, spriteData[0]);
	}
}

void BigEnemy::SetDyingSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[DYING*3]);
		sp->SetFrameWidth(spriteData[DYING*3 + 1]);
		sp->SetFrameCount(spriteData[DYING*3 + 2]);
		sp->SetLine(DYING, spriteData[0]);
	}
}

void BigEnemy::SetAttackingSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[ATTACK*3]);
		sp->SetFrameWidth(spriteData[ATTACK*3 + 1]);
		sp->SetFrameCount(spriteData[ATTACK*3 + 2]);
		sp->SetLine(ATTACK, spriteData[0]);
	}
}

void BigEnemy::SetDistanceToBaon(float distance) {
	distanceToBaon = distance;
}

float BigEnemy::GetDistanceToBaon() {
	return distanceToBaon;
}

bool BigEnemy::HasCollidedHorizontally() {
	return collidedHorizontally;
}

void BigEnemy::InitializeStates() {
	// Initialize all the states in Enemy here.
	this->enemyStatesMap.emplace(ATTACK, new BigEnemyStateAttacking(this));
	this->enemyStatesMap.emplace(TAKINGHIT, new BigEnemyStateTakeDamage(this));
	this->enemyStatesMap.emplace(DYING, new BigEnemyStateDying(this));
	this->enemyStatesMap.emplace(PATROLLING, new BigEnemyStatePatrolling(this));
	this->enemyStatesMap.emplace(FOLLOW, new BigEnemyStateFollow(this));
	this->enemyStatesMap.emplace(BEINGPUSHED, new BigEnemyBeingPushed(this));
	this->enemyStatesMap.emplace(STAND, new BigEnemyStandingState(this));

	currentState = enemyStatesMap.at(PATROLLING);
}

void BigEnemy::InitializeSprite() {
	LoadSpriteData("data/inimigo2-data.txt");

	sp = new Sprite("img/inimigo2.png", 1, 0.1);

	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);

	box.SetX(spawnX + 33*scale);
	box.SetY(ENEMY_MAP_GROUND * scale);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
}

void BigEnemy::InitializeForces() {
	b = new Body("enemy", box.GetX(), box.GetY());

	b->ApplyForce(new Force("gravity", 0, 900));
	b->SetSpeedLimit(1000);
}

void BigEnemy::Initialize() {
	distanceToBaon = 0;
	collidedHorizontally = false;
}
