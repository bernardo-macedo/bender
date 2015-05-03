#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Engine/Game.h"
#include "Engine/TileSet/TileMap.h"

using namespace std;
int main (int argc, char** argv) {
	try{
		Game *gm = new Game("Pedro Henrique Leal - 100019226", 1024, 600);
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
