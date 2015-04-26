/*
 * Timer.h
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "SDL.h"

class Timer {
private:
	bool done;
	bool paused;
	bool started;
	unsigned int goalTimeInMilliseconds;
	unsigned int pausedTimeInMilliseconds;
public:
	Timer();
	virtual ~Timer();

	void Start(int newGoalTimeInMilliseconds);
	void Resume();
	void Pause();
	void Update();
	unsigned int RemainingTime();

	bool IsDone() const {
		return done;
	}
};

#endif /* TIMER_H_ */
