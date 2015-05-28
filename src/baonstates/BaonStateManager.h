/*
 * BaonStateManager.h
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATEMANAGER_H_
#define BAONSTATEMANAGER_H_

class BaonState;
class Timer;

class Baon;
class BaonStateManager {
public:
	BaonStateManager(Baon* baon);
	virtual ~BaonStateManager();

	void Update(float dt);
	BaonState* GetCurrentState();
	BaonState* GetPreviousState();
private:
	BaonState* currentState, *previousState;
	Baon* baon;
	bool executed;
	bool flipped;
	Timer* t;
	int runTest;
};

#endif /* BAONSTATEMANAGER_H_ */
