/*
 * BigEnemyStatePatrolling.h
 *
 *  Created on: Jul 12, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_BIGENEMYSTATEPATROLLING_H_
#define ENEMYSTATES_BIGENEMYSTATEPATROLLING_H_

#include "StateBigEnemy.h"

class BigEnemyStatePatrolling  : public StateBigEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		BigEnemyStatePatrolling(BigEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~BigEnemyStatePatrolling(){}

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

		float patrollDistance;
		float patrollMaxDistance;
		bool isLeft;

};

#endif /* ENEMYSTATES_BIGENEMYSTATEPATROLLING_H_ */
