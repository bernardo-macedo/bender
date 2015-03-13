#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "GameRenderer.h"

using namespace std;
int main (int argc, char** argv) {
	GameRenderer *gm = new GameRenderer("Teste", 500, 500);
	gm->Run();
    return 0;
}
