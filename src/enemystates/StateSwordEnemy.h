/*
 * StateSwordEnemy.h
 *
 *  Created on: Jun 26, 2015
 *      Author: -Bernardo
 */

#ifndef ENEMYSTATES_STATESWORDENEMY_H_
#define ENEMYSTATES_STATESWORDENEMY_H_

class SwordEnemy;

class StateSwordEnemy {
public:
	/**
	* The constructor.
	* @param enemy_ : Reference to the Enemy.
	*/
	StateSwordEnemy(SwordEnemy* const enemy_);

	/**
	* The destructor.
	*/
	virtual ~StateSwordEnemy();

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

	SwordEnemy* enemy; /**< Reference to the enemy. */

protected:
	bool askEnd;
};

#endif /* ENEMYSTATES_STATESWORDENEMY_H_ */
