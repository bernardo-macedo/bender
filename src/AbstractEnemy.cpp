/*
 * AbstractEnemy.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "AbstractEnemy.h"

int AbstractEnemy::ENEMY_MAP_GROUND = 50;

AbstractEnemy::AbstractEnemy(int enemyScale, int x, int hp, int walkSpeed, int runSpeed, float doubleClickTime) {
	this->hp = hp;
	scale = enemyScale;
	spawnX = x;
	WALK_SPEED_E = walkSpeed;
	RUN_SPEED_E = runSpeed;
	DOUBLECLICK_TIME = doubleClickTime;

	t = new Timer();

	flipped = false;
	fallUpdateCount = 0;
	isDead = false;
	isDying  = false;
	isDamage = false;
	isTakingDamage = false;

	runStates = NONE;
}

AbstractEnemy::~AbstractEnemy() {
	delete sp;
	delete t;
}

void AbstractEnemy::Render() {
	if(!isDead){
		sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0, flipped);
	}
}

bool AbstractEnemy::IsDead() {
	return isDead;
}
bool AbstractEnemy::Is(std::string type) {
	return Being::Is(type) || type.compare("Enemy") == 0;
}

void AbstractEnemy::Run(bool flipped) {
	if(!flipped){
		this->flipped = false;
		b->SetVelX(RUN_SPEED_E);
	}
	else{
		this->flipped = true;
		b->SetVelX(-RUN_SPEED_E);
	}
}

void AbstractEnemy::Walk(bool flipped) {
	//SetWalkSprite();

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

void AbstractEnemy::Stand(bool flipped) {
	SetStandSprite();

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

void AbstractEnemy::Jump(bool flipped) {
	SetJumpSprite();

	b->SetVelY(-500);
	b->ApplyForce(new Force("gravity", 0, 900));
}

Sprite* AbstractEnemy::GetSprite(){
	return sp;
}

Timer* AbstractEnemy::GetTimer(){
	return t;
}

int AbstractEnemy::GetSpawnX() {
	return spawnX;
}

int AbstractEnemy::GetHP() {
	return hp;
}

bool AbstractEnemy::GetFlipped() {
	return flipped;
}

bool AbstractEnemy::IsTakingDamage() {
	return isTakingDamage;
}

bool AbstractEnemy::IsRemovable() {
	return isRemovable;
}

bool AbstractEnemy::IsCollisionFromRight() {
	return collisionFromRight;
}

bool AbstractEnemy::IsDying() {
	return isDying;
}

bool AbstractEnemy::IsCloseToBaon() {
	return closeToBaon;
}

void AbstractEnemy::SetCloseToBaon(bool close) {
	closeToBaon = close;
}

void AbstractEnemy::SetTakingDamage(bool damage) {
	this->isTakingDamage = damage;
}

void AbstractEnemy::SetDying(bool dying) {
	this->isDying = dying;
}

void AbstractEnemy::SetDead(bool isDead){
	this->isDead = isDead;
}

void AbstractEnemy::SetFlipped(bool flipped) {
	this->flipped = flipped;
}

void AbstractEnemy::LoadSpriteData(std::string file) {
	FILE *fp = fopen(file.c_str(), "r");
	fscanf(fp, "%d", &numEst);

	int val;
	while(!feof(fp)){
		fscanf(fp, "%d", &val);
		spriteData.push_back(val);
	}
	fclose(fp);
}

EnemyAttack AbstractEnemy::GetLastGivenAttack() {
	return lastGivenAttack;
}

void AbstractEnemy::SetLastGivenAttack(EnemyAttack attack) {
	lastGivenAttack = attack;
}
