/*
 * SwordEnemyStateDying.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_SWORDENEMYSTATEDYING_H_
#define ENEMYSTATES_SWORDENEMYSTATEDYING_H_

#include "StateSwordEnemy.h"
#include "../Engine/Timer.h"
#include "../Engine/Sound.h"

class SwordEnemyStateDying : public StateSwordEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		SwordEnemyStateDying(SwordEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~SwordEnemyStateDying();

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

#endif /* ENEMYSTATES_SWORDENEMYSTATEDYING_H_ */
