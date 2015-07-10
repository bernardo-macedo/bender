/*
 * SwordEnemyAIManager.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#include "SwordEnemyAIManager.h"

SwordEnemyAIManager::SwordEnemyAIManager(Baon* baon_, SwordEnemy* enemy_) {
	this->baon = baon_;
	this->enemy = enemy_;
}

SwordEnemyAIManager::~SwordEnemyAIManager() {}

void SwordEnemyAIManager::update(const float dt) {

	if(!baon->IsDead()){
		enemy->SetDistanceToBaon(enemy->GetBody()->GetX() - baon->GetBody()->GetX());

		if(abs(enemy->GetDistanceToBaon()) < 30*baon->GetScale()){
			if(!enemy->IsState(SwordEnemy::enemyStates::ATTACK)
				&& !enemy->IsState(SwordEnemy::enemyStates::TAKINGHIT)
				&& !enemy->IsState(SwordEnemy::enemyStates::DYING)){

				if (baon->GetBody()->GetX() < enemy->GetBody()->GetX()) {
					enemy->SetFlipped(true);
				}
				enemy->changeState(SwordEnemy::enemyStates::ATTACK);
			}
		} else if(abs(enemy->GetDistanceToBaon()) < 75*baon->GetScale()){
			baon->SetCloseToEnemy(true);
		} else {
			baon->SetCloseToEnemy(false);
			if (abs(enemy->GetDistanceToBaon()) < 150*baon->GetScale() && !enemy->IsState(SwordEnemy::enemyStates::FOLLOW)) {
				if (enemy->IsState(SwordEnemy::enemyStates::PATROLLING) || enemy->StateEnd()) {
					enemy->changeState(SwordEnemy::enemyStates::FOLLOW);
				}
			}
		}

	}
	if(enemy->IsState(SwordEnemy::enemyStates::ATTACK)
			|| enemy->IsState(SwordEnemy::enemyStates::TAKINGHIT)){
		if(enemy->StateEnd()){
			enemy->changeState(SwordEnemy::enemyStates::PATROLLING);
		}
	}

	if(!enemy->IsDead() && enemy->IsTakingDamage() && !enemy->IsDying()){
		if(!enemy->IsState(SwordEnemy::enemyStates::TAKINGHIT)){
			enemy->TakeDamage(true);
			enemy->changeState(SwordEnemy::enemyStates::TAKINGHIT);
		}
		else{
			enemy->SetTakingDamage(false);
		}
	}

	if(!enemy->IsDead() && enemy->IsDying()){
		if(!enemy->IsState(SwordEnemy::enemyStates::DYING)){
			enemy->changeState(SwordEnemy::enemyStates::DYING);
		}
	}

	if(!baon->IsDead()){
		Rect baonRect, enemyRect;

		baonRect.SetX(baon->GetBody()->GetX());
		baonRect.SetY(baon->GetBody()->GetY());
		baonRect.SetW(30*baon->GetScale());
		baonRect.SetH(50*baon->GetScale());

		enemyRect.SetX(enemy->GetBody()->GetX());
		enemyRect.SetY(enemy->GetBody()->GetY());
		enemyRect.SetW(30*enemy->GetScale());
		enemyRect.SetH(50*enemy->GetScale());

		if(Collision::IsColliding(baonRect, enemyRect, 0, 0)){
			bool right;
			if(enemyRect.GetX() > baonRect.GetX()){
				right = true;
			}else{
				right = false;
			}

			if(!enemy->IsDead() && !baon->IsDead()){
				if(baon->isDamage && ((right && !baon->IsFlipped()) || (!right && baon->IsFlipped()))){
					enemy->SetTakingDamage(true);
				}
				if(!baon->isTakingDamage() && enemy->isDamage) {
					if ((right && enemy->GetFlipped()) || (!right && !enemy->GetFlipped())) {
						baon->TakeDamage(true, right);
					}
				}
			}
		}
	}

}

void SwordEnemyAIManager::SetEnemy(SwordEnemy* enemy) {
	this->enemy = enemy;
}
