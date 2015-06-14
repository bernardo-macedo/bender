/*
 * Sprite.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include "Sprite.h"
#include "Game.h"

using namespace std;
Sprite::Sprite() {
	texture = NULL;
	frameCount = 1;
	frameTime = 1;
	timeElapsed = 0;
	frameTime = 0;
	currentFrame = 1;
	scaleX = 1;
	scaleY = 1;
	width = 0;
	height = 0;
	open = false;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime) {
	scaleX = 1;
	scaleY = 1;
	this->frameTime = frameTime;
	timeElapsed = 0;
	this->frameCount = frameCount;
	currentFrame = 1;
	scaleX = 1;
	scaleY = 1;
	width = 0;
	height = 0;
	texture = NULL;
	Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
	texture = Resources::GetImage(file);

	SDL_QueryTexture (texture , NULL, NULL, &width, &height);
	this->frameWidth = width/frameCount;
	SetClip(0, 0, frameWidth, height);
	open = true;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.h = h;
	clipRect.w = w;
}

void Sprite::Render(int x, int y, int angle, bool flipped) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = clipRect.h*scaleY;
	rect.w = clipRect.w*scaleX;
	if(flipped){
		SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect, &rect, angle, NULL, SDL_FLIP_HORIZONTAL);
	}
	else{
		SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect, &rect, angle, NULL, SDL_FLIP_NONE);
	}
}

int Sprite::GetWidth() {
	return width*scaleX;
}

int Sprite::GetHeight() {
	return height*scaleY;
}

bool Sprite::IsOpen() {
	return open;
}

void Sprite::SetScaleX(float scale) {
	this->scaleX = scale;
}

void Sprite::SetScaleY(float scale) {
	this->scaleY = scale;

}

bool Sprite::Update(float dt) {
	timeElapsed += dt;
	if(timeElapsed >= frameTime){
		if(currentFrame + 1 > frameCount){
			clipRect.x = 0;
			currentFrame = 1;
		}
		else{
			clipRect.x += frameWidth;
			currentFrame++;
		}
		timeElapsed = 0;
		return true;
	}
	return false;
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
	if(frame <= frameCount){
		clipRect.x = (frame-1)*frameWidth;
	}
	else{
		clipRect.x = (frameCount-1)*frameWidth;
	}
}

void Sprite::SetFrameCount(int frameCount) {
	this->frameCount = frameCount;
}

int Sprite::GetFrameWidth() {
	return frameWidth;
}

int Sprite::GetFrameHeight() {
	return frameHeight;
}

void Sprite::SetFrameHeight(int frameHeight) {
	this->frameHeight = frameHeight;
	SetClip(clipRect.x, clipRect.y, clipRect.w, frameHeight);
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;
}

void Sprite::SetFrameWidth(int frameWidth) {
	this->frameWidth = frameWidth;
	SetClip(0, 0, this->frameWidth, frameHeight);
}

void Sprite::SetLine(int line, int lineSize) {
	SetClip(0,line*lineSize, this->frameWidth, frameHeight);
	currentFrame = 1;
}

int Sprite::GetCurrentFrame() {
	return currentFrame;
}
