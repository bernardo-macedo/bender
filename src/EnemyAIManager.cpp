#include "EnemyAIManager.h"
#include "Engine/Collision.h"
#include <iostream>

EnemyAIManager::EnemyAIManager(Baon* baon_, Enemy* enemy_){
	this->enemy = enemy_;
	this->baon = baon_;
}

EnemyAIManager::~EnemyAIManager(){
	
}

void EnemyAIManager::update(const float dt){
	if(!baon->IsDead()){
		if(abs(enemy->GetBody()->GetX() - baon->GetBody()->GetX()) < 25*baon->GetScale()){
			if(!enemy->IsState(Enemy::enemyStates::PUNCH)){
				enemy->changeState(Enemy::enemyStates::PUNCH);
			}
		}

		if(abs(enemy->GetBody()->GetX() - baon->GetBody()->GetX()) < 75*baon->GetScale()){
			baon->SetCloseToEnemy(true);
		}

		if(abs(enemy->GetBody()->GetX() - baon->GetBody()->GetX()) > 70*baon->GetScale()
				&& abs(enemy->GetBody()->GetX() - baon->GetBody()->GetX()) < 140*baon->GetScale()){
			if(((enemy->GetBody()->GetX() < baon->GetBody()->GetX()) && (!enemy->GetFlipped()))
				|| ((enemy->GetBody()->GetX() > baon->GetBody()->GetX()) && (enemy->GetFlipped()))){
				if(!enemy->IsState(Enemy::enemyStates::BEND)
					&& !enemy->IsState(Enemy::enemyStates::TAKINGHIT)
					&& (enemy->GetCoolDown() <= 0)){

					enemy->changeState(Enemy::enemyStates::BEND);
				}
			}
		}
	}
	if(enemy->IsState(Enemy::enemyStates::PUNCH)
			|| enemy->IsState(Enemy::enemyStates::BEND)
			|| enemy->IsState(Enemy::enemyStates::TAKINGHIT)){
		if(enemy->StateEnd()){
			enemy->changeState(Enemy::enemyStates::PATROLLING);
		}
	}

	if(enemy->IsState(Enemy::enemyStates::FOLLOW)){
		int baonX = baon->GetBody()->GetX();
		int enemyX = enemy->GetBody()->GetX();

		// Esse 30 tem que tirar depois, e so pra nao ficar trocando entre os ifs.
		if(baonX - 30 > enemyX){
			enemy->Run(false);
		}
		else if(baonX < enemyX){
			enemy->Run(true);	
		}
	}

	if(!enemy->IsDead() && enemy->IsTakingDamage()){
		if(!enemy->IsState(Enemy::enemyStates::TAKINGHIT)){
			enemy->TakeDamage(true);
			enemy->changeState(Enemy::enemyStates::TAKINGHIT);
		}
		else{
			enemy->SetTakingDamage(false);
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
				if(baon->isDamage){
					enemy->SetTakingDamage(true);
				}
				if(!baon->isTakingDamage() && enemy->isDamage){
					baon->TakeDamage(true, right);
				}
			}
		}
	}
}

void EnemyAIManager::SetEnemy(Enemy* enemy) {
	this->enemy = enemy;
}
