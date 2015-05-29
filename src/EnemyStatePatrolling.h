#ifndef INCLUDE_ENEMYSTATEPATROLLING_H
#define INCLUDE_ENEMYSTATEPATROLLING_H

#include "StateEnemy.h"

class EnemyStatePatrolling : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStatePatrolling(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStatePatrolling(){}

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

#endif // INCLUDE_ENEMYSTATEPATROLLING_H
