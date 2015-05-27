#ifndef INCLUDE_ENEMYSTATEFOLLOW_H
#define INCLUDE_ENEMYSTATEFOLLOW_H

#include "StateEnemy.h"

class EnemyStateFollow : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EnemyStateFollow(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EnemyStateFollow(){}

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
		virtual void update(float dt_);

};

#endif // INCLUDE_ENEMYSTATEFOLLOW_H
