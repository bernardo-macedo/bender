/*
 * EnemyStateTakeDamage.cpp
 *
 *  Created on: 25/06/2015
 *      Author: Pedro2
 */

#include "EnemyStateTakeDamage.h"

#include "Enemy.h"
#include "Engine/Physics/Body.h"
#include "Engine/Physics/Force.h"
#include "Engine/Sprite.h"

EnemyStateTakeDamage::EnemyStateTakeDamage(Enemy* const enemy_) :
	StateEnemy(enemy_)
{

}

void EnemyStateTakeDamage::enter() {
	askEnd = false;
	enemy->GetSprite()->SetFrameWidth(36);
	enemy->GetSprite()->SetFrameHeight(50);
	enemy->GetSprite()->SetFrameCount(7);
	enemy->GetSprite()->SetLine(4, 50);
	enemy->GetSprite()->SetFrameTime(0.1);
	if(enemy->IsCollisionFromRight()){
		enemy->GetBody()->SetVelX(-100);
		enemy->GetBody()->ApplyForce(new Force("resistance", 150, 0));
	}
	else{
		enemy->GetBody()->SetVelX(100);
		enemy->GetBody()->ApplyForce(new Force("resistance", -150, 0));
	}
}

void EnemyStateTakeDamage::exit() {
	enemy->GetBody()->SetVelX(0);
	enemy->GetBody()->clearForces();
	enemy->SetTakingDamage(false);
	enemy->GetSprite()->SetFrameTime(0.1);
	if(enemy->GetHP() <= 0){
		enemy->SetDying(true);
	}
}

void EnemyStateTakeDamage::update(const float dt_) {
	if(enemy->GetSprite()->GetCurrentFrame() < 7){
		enemy->GetSprite()->Update(dt_);
	}
	else{
		askEnd = true;
	}
}
