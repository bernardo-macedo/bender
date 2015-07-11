/*
 * StateBigEnemy.h
 *
 *  Created on: Jul 11, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_STATEBIGENEMY_H_
#define ENEMYSTATES_STATEBIGENEMY_H_

#include "../BigEnemy.h"

class StateBigEnemy {

public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		StateBigEnemy(BigEnemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~StateBigEnemy();

		/**
		* Method called on load.
		* Pure virtual function. Called on state enter.
		*/
		virtual void enter() = 0;

		/**
		* Method called on unload.
		* Pure virtual function. Called on state exit.
		*/
		virtual void exit() = 0;

		/**
		* Update method for the state.
		* While the Enemy is on the state, this method runs every update.
		*/
		virtual void update(const float dt_) = 0;

		bool AskEnd();

		BigEnemy* enemy; /**< Reference to the enemy. */

	protected:
		bool askEnd;
};

#endif /* ENEMYSTATES_STATEBIGENEMY_H_ */
