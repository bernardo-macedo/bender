/*
 * SwordEnemy.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemy.h"

#include "enemystates/SwordEnemyBeingPunched.h"
#include "enemystates/SwordEnemyStandingState.h"
#include "enemystates/SwordEnemyStateAttacking.h"
#include "enemystates/SwordEnemyStateDying.h"
#include "enemystates/SwordEnemyStateFollow.h"
#include "enemystates/SwordEnemyStatePatrolling.h"
#include "enemystates/SwordEnemyStateTakeDamage.h"
#include "Engine/Collision.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Force.h"
#include "Engine/Physics/Physic.h"
#include "Engine/Sprite.h"
#include "SpikeStone.h"

SwordEnemy::SwordEnemy(int enemyScale, int x) : AbstractEnemy(enemyScale, x, 3, 50, 130, 0.2) {
	SetID(GameObject::SWORD_ENEMY);
	InitializeSprite();
	InitializeStates();
	InitializeForces();
	Initialize();
	this->currentState->enter();
}

SwordEnemy::~SwordEnemy() {
	delete kickhit;
	delete punchhit;
	delete rockHit;
	delete currentState;
}

void SwordEnemy::changeState(const enemyStates state_) {
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

void SwordEnemy::Update(float dt) {
	collidedHorizontally = false;
	if(!isDead) {
		currentState->update(dt);
		if(currentState->AskEnd()){
			if(IsState(BEINGPUSHED)){
				isTakingDamage = true;
			}
			changeState(SwordEnemy::PATROLLING);
		}
		Physic::GetInstance()->UpdatePhysic(b, dt);
	} else {
		isRemovable = true;
	}

	box.SetX(b->GetX());

	//if (IsState(enemyStates::DYING)) {
		// Necessario pq o sprite de morte esta em perspectiva
	//	box.SetY(b->GetY() + 5);
	//} else {
		box.SetY(b->GetY());
	//}
}

void SwordEnemy::NotifyCollision(GameObject* other) {
	if(other->GetID() == GameObject::PEDRA_BASICO_BAON
			|| other->GetID() == GameObject::CONTROLE_BEND){
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
		if(!IsState(SwordEnemy::BEINGPUSHED)
				&& !IsState(SwordEnemy::TAKINGHIT)
				&& !IsState(SwordEnemy::DYING)){
			if(pedra->GetFlipped()){
				collisionFromRight = true;
			}
			else{
				collisionFromRight = false;
			}
			changeState(SwordEnemy::BEINGPUSHED);
		}
	}

	if(other->GetID() == GameObject::PEDRA_DEFESA){
		if(!IsState(SwordEnemy::STAND)){
			changeState(SwordEnemy::STAND);
		}
	}
}

void SwordEnemy::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {
	if (collisionAxis == Collision::CollisionAxis::AXIS_X) {
		collidedHorizontally = true;
	}
}

bool SwordEnemy::Is(std::string type) {
	return AbstractEnemy::Is(type) || type.compare("SwordEnemy") == 0;
}

void SwordEnemy::InitializeStates() {
	// Initialize all the states in Enemy here.
	this->enemyStatesMap.emplace(ATTACK, new SwordEnemyStateAttacking(this));
	this->enemyStatesMap.emplace(TAKINGHIT, new SwordEnemyStateTakeDamage(this));
	this->enemyStatesMap.emplace(DYING, new SwordEnemyStateDying(this));
	this->enemyStatesMap.emplace(PATROLLING, new SwordEnemyStatePatrolling(this));
	this->enemyStatesMap.emplace(FOLLOW, new SwordEnemyStateFollow(this));
	this->enemyStatesMap.emplace(BEINGPUSHED, new SwordEnemyBeingPushed(this));
	this->enemyStatesMap.emplace(STAND, new SwordEnemyStandingState(this));

	currentState = enemyStatesMap.at(PATROLLING);
}

void SwordEnemy::InitializeSprite() {
	LoadSpriteData("data/inimigo1-data.txt");

	sp = new Sprite("img/inimigo1.png", 1, 0.1);

	sp->SetFrameHeight(spriteData[0]);
	sp->SetFrameWidth(spriteData[1]);

	box.SetX(spawnX + 33*scale);
	box.SetY(ENEMY_MAP_GROUND * scale);
	box.SetH(sp->GetFrameHeight());
	box.SetW(sp->GetFrameWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
}

void SwordEnemy::InitializeForces() {
	b = new Body("enemy", box.GetX(), box.GetY());

	b->ApplyForce(new Force("gravity", 0, 900));
	b->SetSpeedLimit(1000);
}

bool SwordEnemy::HasCollidedHorizontally() {
	return collidedHorizontally;
}

void SwordEnemy::Initialize() {
	distanceToBaon = 0;
	collidedHorizontally = false;

	punchhit = new Sound("audio/sfx_char_punch_hit1.wav");
	kickhit = new Sound("audio/sfx_char_kick_hit1.wav");
	rockHit = new Sound("audio/sfx_throwRock_hit.wav");
}

void SwordEnemy::SetWalkSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[WALK*3]);
		sp->SetFrameWidth(spriteData[WALK*3 + 1]);
		sp->SetFrameCount(spriteData[WALK*3 + 2]);
		sp->SetLine(WALK, spriteData[0]);
	}
}

void SwordEnemy::SetStandSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[STAND*3]);
		sp->SetFrameWidth(spriteData[STAND*3 + 1]);
		sp->SetFrameCount(1);
		sp->SetLine(STAND, spriteData[0]);
	}
}

void SwordEnemy::SetJumpSprite() {}

void SwordEnemy::SetTakingDamageSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[TAKINGHIT*3]);
		sp->SetFrameWidth(spriteData[TAKINGHIT*3 + 1]);
		sp->SetFrameCount(spriteData[TAKINGHIT*3 + 2]);
		sp->SetLine(TAKINGHIT, spriteData[0]);
	}
}

void SwordEnemy::SetDyingSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[DYING*3]);
		sp->SetFrameWidth(spriteData[DYING*3 + 1]);
		sp->SetFrameCount(spriteData[DYING*3 + 2]);
		sp->SetLine(DYING, spriteData[0]);
	}
}

void SwordEnemy::SetAttackingSprite() {
	if (sp != NULL) {
		sp->SetFrameHeight(spriteData[ATTACK*3]);
		sp->SetFrameWidth(spriteData[ATTACK*3 + 1]);
		sp->SetFrameCount(spriteData[ATTACK*3 + 2]);
		sp->SetLine(ATTACK, spriteData[0]);
	}
}

void SwordEnemy::SetDistanceToBaon(float distance) {
	distanceToBaon = distance;
}

float SwordEnemy::GetDistanceToBaon() {
	return distanceToBaon;
}

