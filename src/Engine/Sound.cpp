/*
 * Sound.cpp
 *
 *  Created on: 21/05/2015
 *      Author: Pedro2
 */

#include "Sound.h"
#include "Resources.h"

Sound::Sound() {
	sound = NULL;
	channel = -1;
}

Sound::Sound(std::string file) {
	Open(file);
	channel = -1;
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, sound, times);
}

void Sound::Stop() {
	if (channel != -1) {
		Mix_HaltChannel(channel);
	}
}

void Sound::Open(std::string file) {
	sound = Resources::GetSound(file);
}

bool Sound::IsOpen() {
	return sound != NULL;
}
