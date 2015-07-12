/*
 * BigEnemyStateTakeDamage.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_BigENEMYSTATETAKEDAMAGE_H_
#define ENEMYSTATES_BigENEMYSTATETAKEDAMAGE_H_

#include "StateBigEnemy.h"

class BigEnemyStateTakeDamage : public StateBigEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		BigEnemyStateTakeDamage(BigEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~BigEnemyStateTakeDamage() {}

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
};

#endif /* ENEMYSTATES_BigENEMYSTATETAKEDAMAGE_H_ */
