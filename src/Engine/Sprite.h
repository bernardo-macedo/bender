/*
 * Sprite.h
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include <iostream>
#include "GameObject.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Exceptions.h"

class Sprite : public GameObject{
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	bool open;
	SDL_Point center;
public:
	Sprite(std::string file, std::string id, float x, float y) : GameObject(id, x, y){
		texture = NULL;
		open = false;
		Open(file);
	}
	Sprite(std::string id, float x, float y) : GameObject(id, x, y){
		texture = NULL;
		open = false;
		width = 0;
		height = 0;
	}
	virtual ~Sprite();

	void Open(std::string file);
	void SetClip (int x, int y, int w, int h);
	void OnRender();
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	void SetCenter(int cX, int cY);
};

#endif /* ENGINE_SPRITE_H_ */
