/*
 * Sprite.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include <iostream>
#include "SDL_render.h"
#include "SDL_image.h"
#include "Exceptions.h"
#include "Resources.h"
#include <memory>

class Sprite {
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	bool open;
	float scaleX, scaleY;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
public:
	Sprite();
	Sprite(std::string file, int frameCount = 1, float frameTime = 1);
	virtual ~Sprite();

	void Open(std::string file);
	void SetClip (int x, int y, int w, int h);
	void Render(int x, int y, int angle = 0);
	int GetWidth();
	int GetFrameWidth();
	int GetHeight();
	bool IsOpen();
	void SetScaleX(float scale);
	void SetScaleY(float scale);

	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
};

#endif /* ENGINE_SPRITE_H_ */
