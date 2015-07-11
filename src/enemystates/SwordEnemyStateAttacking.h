/*
 * SwordEnemyStateAttacking.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_SWORDENEMYSTATEATTACKING_H_
#define ENEMYSTATES_SWORDENEMYSTATEATTACKING_H_

#include "StateSwordEnemy.h"
#include "../Engine/Sound.h"
#include "../EnemyAttack.h"

class SwordEnemyStateAttacking : public StateSwordEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		SwordEnemyStateAttacking(SwordEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~SwordEnemyStateAttacking();

		/**
		* @see StateEnemy::enter
		*/
		virtual void enter();

		/**
		* @see StateEnemy::exit
		*/
		virtual void exit();

		/**
		* @see StateEnemy::update
		*/
		virtual void update(const float dt_);

	private:

		Sound* swordSwingSound;
};

#endif /* ENEMYSTATES_SWORDENEMYSTATEATTACKING_H_ */
