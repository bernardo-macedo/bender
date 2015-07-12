/*
 * BigEnemyAIManager.cpp
 *
 *  Created on: Jul 12, 2015
 *      Author: -Bernardo
 */

#include "BigEnemyAIManager.h"

BigEnemyAIManager::BigEnemyAIManager(Baon* baon_, BigEnemy* enemy_) {
	this->baon = baon_;
	this->enemy = enemy_;
}

BigEnemyAIManager::~BigEnemyAIManager() {
	// TODO Auto-generated destructor stub
}

void BigEnemyAIManager::update(const float dt) {
	if(!baon->IsDead()){
		enemy->SetDistanceToBaon(enemy->GetBody()->GetX() - baon->GetBody()->GetX());

		if(abs(enemy->GetDistanceToBaon()) < 30*baon->GetScale() && abs(enemy->GetBody()->GetY() - baon->GetBody()->GetY()) < enemy->GetBox().GetH()){
			if(!enemy->IsState(BigEnemy::enemyStates::ATTACK)
				&& !enemy->IsState(BigEnemy::enemyStates::TAKINGHIT)
				&& !enemy->IsState(BigEnemy::enemyStates::DYING)
				&& !enemy->IsState(BigEnemy::enemyStates::BEINGPUSHED)){

				if (baon->GetBody()->GetX() < enemy->GetBody()->GetX()) {
					enemy->SetFlipped(true);
				}
				enemy->changeState(BigEnemy::enemyStates::ATTACK);
			}
		} else if(abs(enemy->GetDistanceToBaon()) < 75*baon->GetScale()){
			baon->SetCloseToEnemy(true);
		} else {
			baon->SetCloseToEnemy(false);
			if (abs(enemy->GetDistanceToBaon()) < 150*baon->GetScale() && !enemy->IsState(BigEnemy::enemyStates::FOLLOW)) {
				if (enemy->IsState(BigEnemy::enemyStates::PATROLLING) || enemy->StateEnd()) {
					enemy->changeState(BigEnemy::enemyStates::FOLLOW);
				}
			}
		}

	}
	if(enemy->IsState(BigEnemy::enemyStates::ATTACK)
			|| enemy->IsState(BigEnemy::enemyStates::TAKINGHIT)){
		if(enemy->StateEnd()){
			enemy->changeState(BigEnemy::enemyStates::PATROLLING);
		}
	}

	if(!enemy->IsDead() && enemy->IsTakingDamage() && !enemy->IsDying()){
		if(!enemy->IsState(BigEnemy::enemyStates::TAKINGHIT)){
			enemy->TakeDamage(baon->GetLastGivenAttack());
			enemy->changeState(BigEnemy::enemyStates::TAKINGHIT);
		}
		else{
			enemy->SetTakingDamage(false);
		}
	}

	if(!enemy->IsDead() && enemy->IsDying()){
		if(!enemy->IsState(BigEnemy::enemyStates::DYING)){
			enemy->changeState(BigEnemy::enemyStates::DYING);
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
						baon->TakeDamage(enemy->GetLastGivenAttack(), true, right);
					}
				}
			}
		}
	}
}

void BigEnemyAIManager::SetEnemy(BigEnemy* enemy) {
	this->enemy = enemy;
}
