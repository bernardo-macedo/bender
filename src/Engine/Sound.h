/*
 * Sound.h
 *
 *  Created on: 21/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_SOUND_H_
#define ENGINE_SOUND_H_

#include <iostream>
#include "SDL_Wrapper.h"
 
class Sound {
public:
private:
	Mix_Chunk* sound;
	int channel;
public:
	Sound();
	Sound(std::string file);

	void Play(int times);
	void Stop();

	void Open(std::string file);
	bool IsOpen();

	static int ALWAYS;
};

#endif /* ENGINE_SOUND_H_ */
