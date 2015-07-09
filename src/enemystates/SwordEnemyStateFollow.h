/*
 * SwordEnemyStateFollow.h
 *
 *  Created on: Jul 9, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_SWORDENEMYSTATEFOLLOW_H_
#define ENEMYSTATES_SWORDENEMYSTATEFOLLOW_H_

#include "StateSwordEnemy.h"

class SwordEnemyStateFollow : public StateSwordEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		SwordEnemyStateFollow(SwordEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~SwordEnemyStateFollow() {}

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

#endif /* ENEMYSTATES_SWORDENEMYSTATEFOLLOW_H_ */
