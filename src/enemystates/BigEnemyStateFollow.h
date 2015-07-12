/*
 * BigEnemyStateFollow.h
 *
 *  Created on: Jul 12, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_BIGENEMYSTATEFOLLOW_H_
#define ENEMYSTATES_BIGENEMYSTATEFOLLOW_H_

#include "StateBigEnemy.h"

class BigEnemyStateFollow : public StateBigEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		BigEnemyStateFollow(BigEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~BigEnemyStateFollow() {}

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

#endif /* ENEMYSTATES_BIGENEMYSTATEFOLLOW_H_ */
