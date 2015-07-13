/*
 * EnemyStateBend.cpp
 *
 *  Created on: 19/06/2015
 *      Author: Pedro2
 */

#include "BenderEnemyStateBend.h"

#include <stddef.h>

#include "../Enemy.h"
#include "../Engine/Game.h"
#include "../Engine/Physics/Body.h"
#include "../Engine/Sprite.h"
#include "../Engine/State.h"
#include "../Engine/GameObject.h"

EnemyStateBend::EnemyStateBend(Enemy* const enemy_)  :
StateEnemy(enemy_)
{
	pedra = NULL;
}
// TODO Auto-generated constructor stub

EnemyStateBend::~EnemyStateBend() {
	// TODO Auto-generated destructor stub
}

void EnemyStateBend::enter() {
	enemy->GetBody()->SetVelX(0);
	enemy->GetSprite()->SetFrameHeight(50);
	enemy->GetSprite()->SetFrameWidth(36);
	enemy->GetSprite()->SetFrameCount(5);
	enemy->GetSprite()->SetLine(3, 50);

	if(!enemy->GetFlipped()){
		pedra = new PedraBasico(enemy->GetBox().GetX() + 30*enemy->GetScale(),
				enemy->GetBox().GetY() + 25*enemy->GetScale(), enemy->GetScale(), this);
		pedra->SetID(GameObject::PEDRA_BASICO_ENEMY);
	}
	else{
		pedra = new PedraBasico(enemy->GetBox().GetX() - 30*enemy->GetScale(),
				enemy->GetBox().GetY() + 25*enemy->GetScale(), enemy->GetScale(), this);
		pedra->SetID(GameObject::PEDRA_BASICO_ENEMY);
	}

	pedra->SetRockSprite(0.04);
	Game::GetInstance()->GetCurrentState()->AddObject(pedra);

	askEnd = false;

	enemy->SetLastGivenAttack(EnemyAttack::ROCK);
}

void EnemyStateBend::exit() {
	if(pedra != NULL && !pedra->Isthrown()){
		pedra->SetDead(true);
	}
}

void EnemyStateBend::update(const float dt_) {
	enemy->GetSprite()->Update(dt_);
	if(enemy->GetSprite()->GetCurrentFrame() >= 5){
		if (pedra != NULL) {
			if(!enemy->GetFlipped()){
				pedra->GetBody()->SetVelX(1000);
				pedra->GetBody()->SetVelY(0);
				pedra->SetGoingLeft(false);
			}
			else{
				pedra->GetBody()->SetVelX(-1000);
				pedra->GetBody()->SetVelY(0);
				pedra->SetGoingLeft(true);
			}
			pedra->SetThrown(true);
			enemy->SetCoolDown(2);
		}
		askEnd = true;
	}
	else{
		if(pedra != NULL){
			if(!pedra->IsFinnished()){
				//pedra->GetSprite()->Update(dt_);
			}
			else{
				pedra->GetBody()->SetVelY(-300);
			}
		}
	}
}

void EnemyStateBend::OnRockDead() {
	pedra = NULL;
}
