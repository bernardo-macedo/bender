/*
 * SwordEnemyPatrolling.h
 *
 *  Created on: Jun 26, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_SWORDENEMYPATROLLING_H_
#define ENEMYSTATES_SWORDENEMYPATROLLING_H_

#include "SwordEnemy.h"
#include "StateSwordEnemy.h"

class SwordEnemyPatrolling : public StateSwordEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		SwordEnemyPatrolling(SwordEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~SwordEnemyPatrolling();

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

#endif /* ENEMYSTATES_SWORDENEMYPATROLLING_H_ */
