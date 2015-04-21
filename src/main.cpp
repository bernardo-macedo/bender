#include <iostream>
#include "Engine/Game.h"
#include "Engine/TileSet/TileMap.h"
#include "Engine/Constants.h"

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

using namespace std;
int main (int argc, char** argv) {
	try{
		Game *gm = new Game(Constants::GameTitle, 1024, 600);
		gm->Run();
	}catch(int e){
		switch(e){
		case WINDOW_FAIL:
			cout << "Erro ao abrir uma janela!" << endl;
			break;
		case RENDERER_FAIL:
			cout << "Erro ao iniciar um renderizador!" << endl;
			break;
		case IMG_LOAD_FAIL:
			cout << "Erro ao abrir uma imagem!" << endl;
			break;
		case INDEX_OUT_OF_RANGE:
			cout << "Indice invalido" << endl;
			break;
		}
	}
    return 0;
}
