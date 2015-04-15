/*
 * Sprite.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Exceptions.h"
#include "Resources.h"

class Sprite {
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	bool open;
	Resources* resources;
public:
	Sprite();
	Sprite(std::string file);
	virtual ~Sprite();

	void Open(std::string file);
	void SetClip (int x, int y, int w, int h);
	void Render(int x, int y);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
};

#endif /* ENGINE_SPRITE_H_ */
