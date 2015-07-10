/*
 * SwordEnemyStatePatrolling.h
 *
 *  Created on: Jul 8, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_SWORDENEMYSTATEPATROLLING_H_
#define ENEMYSTATES_SWORDENEMYSTATEPATROLLING_H_

#include "StateSwordEnemy.h"

class SwordEnemyStatePatrolling : public StateSwordEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		SwordEnemyStatePatrolling(SwordEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~SwordEnemyStatePatrolling(){}

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

#endif /* ENEMYSTATES_SWORDENEMYSTATEPATROLLING_H_ */
