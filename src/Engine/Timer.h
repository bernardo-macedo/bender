/*
 * Timer.h
 *
 *  Created on: 19/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_TIMER_H_
#define ENGINE_TIMER_H_

class Timer {
private:
	float time;
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();
};

#endif /* ENGINE_TIMER_H_ */
