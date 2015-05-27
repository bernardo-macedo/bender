/*
 * Music.h
 *
 *  Created on: 20/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_MUSIC_H_
#define ENGINE_MUSIC_H_

#include "SDL_Wrapper.h"
#include <iostream>

class Music {
private:
	Mix_Music* music;
public:
	Music();
	Music(std::string file);

	void Play(int times);
	void Stop();

	void Open(std::string file);
	bool IsOpen();

	static int ALWAYS;
};

#endif /* ENGINE_MUSIC_H_ */
