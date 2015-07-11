/*
 * BigEnemy.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: -Bernardo
 */

#include "BigEnemy.h"

BigEnemy::BigEnemy(int enemyScale, int x) : AbstractEnemy(enemyScale, x, 2, 50, 130, 0.2) {
}

BigEnemy::~BigEnemy() {
	// TODO Auto-generated destructor stub
}

void BigEnemy::changeState(const enemyStates state_) {
}

bool BigEnemy::IsState(const enemyStates state_) {
}

bool BigEnemy::StateEnd() {
}

void BigEnemy::Update(float dt) {
}

void BigEnemy::NotifyCollision(GameObject* other) {
}

void BigEnemy::NotifyTileCollision(Collision::CollisionAxis collisionAxis) {
}

bool BigEnemy::Is(std::string type) {
}

void BigEnemy::TakeDamage(BaonAttack attack) {
}

void BigEnemy::SetWalkSprite() {
}

void BigEnemy::SetStandSprite() {
}

void BigEnemy::SetJumpSprite() {
}

void BigEnemy::SetTakingDamageSprite() {
}

void BigEnemy::SetDyingSprite() {
}

void BigEnemy::SetAttackingSprite() {
}

void BigEnemy::SetDistanceToBaon(float distance) {
}

float BigEnemy::GetDistanceToBaon() {
}

bool BigEnemy::HasCollidedHorizontally() {
}

void BigEnemy::InitializeStates() {
}

void BigEnemy::InitializeSprite() {
}

void BigEnemy::InitializeForces() {
}

void BigEnemy::Initialize() {
}
