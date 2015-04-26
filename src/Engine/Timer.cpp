/*
 * Timer.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#include "Timer.h"

Timer::Timer() {
	done = false;
	paused = false;
	started = false;
	goalTimeInMilliseconds = 0;
	pausedTimeInMilliseconds = 0;
}

Timer::~Timer() {
}

void Timer::Update() {
	if (!done && !paused && started
			&& SDL_GetTicks() >= goalTimeInMilliseconds) {
		done = true;
		started = false;
	}
}

void Timer::Start(int newGoalTimeInMilliseconds) {
	this->goalTimeInMilliseconds = SDL_GetTicks() + newGoalTimeInMilliseconds;
	done = false;
	paused = false;
	started = true;
}

void Timer::Pause() {
	if (!paused && started) {
		paused = true;
		pausedTimeInMilliseconds = SDL_GetTicks();
	}
}

void Timer::Resume() {
	if (paused) {
		paused = false;
		goalTimeInMilliseconds = goalTimeInMilliseconds
				+ (SDL_GetTicks() - pausedTimeInMilliseconds);
	}
}

unsigned int Timer::RemainingTime() {
	if (done || !started) {
		return 0;
	}
	if (paused) {
		return goalTimeInMilliseconds - pausedTimeInMilliseconds;
	}
	return goalTimeInMilliseconds - SDL_GetTicks();
}
