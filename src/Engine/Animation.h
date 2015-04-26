/*
 * Animation.h
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Sprite.h"
#include "Timer.h"

class Animation {
private:
	Sprite* animationSheet;
	int frameWidth;
	int frameHeight;
	int frameTime;
	int currentFrame;
	bool looping;
	Timer timer;

public:
	Animation(std::string animationSheet, int frameWidth, int frameHeight, int frameTime, bool looping);
	virtual ~Animation();

	void Update();
	void Render(int x, int y);

	int GetFrameHeight() const {
		return frameHeight;
	}

	void SetFrameHeight(int frameHeight) {
		this->frameHeight = frameHeight;
	}

	int GetFrameTime() const {
		return frameTime;
	}

	void SetFrameTime(int frameTime) {
		this->frameTime = frameTime;
	}

	int GetFrameWidth() const {
		return frameWidth;
	}

	void SetFrameWidth(int frameWidth) {
		this->frameWidth = frameWidth;
	}
};

#endif /* ANIMATION_H_ */
