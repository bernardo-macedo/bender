/*
 * Animation.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#include "Animation.h"

Animation::Animation(std::string animation, int frameWidth, int frameHeight, int frameTime, bool looping) :
		frameWidth(frameWidth), frameHeight(frameHeight), frameTime(frameTime), currentFrame(0), looping(looping) {
	animationSheet = new Sprite(animation);
	timer.Start(frameTime);
}

Animation::~Animation() {
}

void Animation::Update() {
	timer.Update();
	if (timer.IsDone()) {
		timer.Start(frameTime);
		currentFrame++;
		currentFrame %= (animationSheet->GetWidth() / frameWidth);
	}

	animationSheet->SetClip(currentFrame * frameWidth, 0, frameWidth, frameHeight);
}

void Animation::Render(int x, int y) {
	animationSheet->Render(x, y);
}
