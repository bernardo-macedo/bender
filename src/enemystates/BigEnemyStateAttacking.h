/*
 * BigEnemyStateAttacking.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_BigENEMYSTATEATTACKING_H_
#define ENEMYSTATES_BigENEMYSTATEATTACKING_H_

#include "StateBigEnemy.h"
#include "../Engine/Sound.h"
#include "../EnemyAttack.h"

class BigEnemyStateAttacking : public StateBigEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		BigEnemyStateAttacking(BigEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~BigEnemyStateAttacking();

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

		Sound* shoulderSwingSound;
};

#endif /* ENEMYSTATES_BigENEMYSTATEATTACKING_H_ */
