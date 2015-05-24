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
	SetClip(0, 0, width/frameCount, height);
	open = true;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.h = h;
	clipRect.w = w;
}

void Sprite::Render(int x, int y, int angle) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.h = clipRect.h*scaleY;
	rect.w = clipRect.w*scaleX;
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect, &rect, angle, NULL, SDL_FLIP_NONE);
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

void Sprite::Update(float dt) {
	timeElapsed += dt;
	float frameW = width/frameCount;
	if(timeElapsed >= frameTime){
		if(clipRect.x + frameW + 1 >= width){
			clipRect.x = 0;
			currentFrame = 0;
		}
		else{
			clipRect.x += frameW;
		}
		timeElapsed = 0;
	}
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
	clipRect.x = frame*(width/frameCount);
}

void Sprite::SetFrameCount(int frameCount) {
	this->frameCount = frameCount;
}

int Sprite::GetFrameWidth() {
	return width/frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;
}
