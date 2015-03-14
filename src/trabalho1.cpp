#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Engine/GameRenderer.h"
#include "MyState.h"

using namespace std;
int main (int argc, char** argv) {
	try{
		GameRenderer *gm = new GameRenderer("IdeiaGlimpse", 500, 500);
		gm->SetStateManager(new MyState());
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
		}
	}
    return 0;
}
