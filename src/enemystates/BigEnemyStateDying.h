/*
 * BigEnemyStateDying.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_BigENEMYSTATEDYING_H_
#define ENEMYSTATES_BigENEMYSTATEDYING_H_

#include "StateBigEnemy.h"
#include "../Engine/Timer.h"
#include "../Engine/Sound.h"

class BigEnemyStateDying : public StateBigEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		BigEnemyStateDying(BigEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~BigEnemyStateDying();

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
		Timer* t;
		Sound* dyingSound;
};

#endif /* ENEMYSTATES_BigENEMYSTATEDYING_H_ */
