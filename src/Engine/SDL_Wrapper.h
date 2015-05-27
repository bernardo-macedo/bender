#ifndef INCLUDE_SDL_WRAPPER_H
#define INCLUDE_SDL_WRAPPER_H

#ifdef __linux__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#elif _WIN32

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#else     

#error Platform not supported

#endif

#endif /* SDL_WRAPPER_H */