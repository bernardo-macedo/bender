/*
 * SwordEnemyStateTakeDamage.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_SWORDENEMYSTATETAKEDAMAGE_H_
#define ENEMYSTATES_SWORDENEMYSTATETAKEDAMAGE_H_

#include "StateSwordEnemy.h"

class SwordEnemyStateTakeDamage : public StateSwordEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		SwordEnemyStateTakeDamage(SwordEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~SwordEnemyStateTakeDamage() {}

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

#endif /* ENEMYSTATES_SWORDENEMYSTATETAKEDAMAGE_H_ */
