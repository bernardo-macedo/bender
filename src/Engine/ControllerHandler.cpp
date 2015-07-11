#include "ControllerHandler.h"
#include "InputManager.h"

#include <iostream>

using namespace std;
ControllerHandler::ControllerHandler() :
    gameController(nullptr)
{

	if(SDL_NumJoysticks() > 0){
         this->gameController = SDL_GameControllerOpen(0);
 	}

	if(this->gameController == nullptr){
		cout << "Unable to find a controller, defaulting to keyboard." << std::endl;
    }

    this->controllStates.fill(false);


}

void ControllerHandler::handleInput(SDL_Event& sdlEvent_){

    static int pressed = 0;    

    if(sdlEvent_.type == SDL_CONTROLLERBUTTONDOWN){

        switch(sdlEvent_.cbutton.button){
        	case controllerMap::buttons::FACE_UP: // Bend key.
				if(!(pressed & (1 << controllerMap::buttons::FACE_UP))){
					InputManager::GetInstance().SetKeyPressed(SDLK_UP);
					pressed |= (1 << controllerMap::buttons::FACE_UP);
				}
			break;

        	case controllerMap::buttons::FACE_RIGHT: // Jump and Bend key.
                if(!(pressed & (1 << controllerMap::buttons::FACE_RIGHT))){
                    InputManager::GetInstance().SetKeyPressed(SDLK_RIGHT);
                    pressed |= (1 << controllerMap::buttons::FACE_RIGHT);
                }
            break;

            case controllerMap::buttons::FACE_LEFT: // Kick and Bend key.
                if(!(pressed & (1 << controllerMap::buttons::FACE_LEFT))){
                    InputManager::GetInstance().SetKeyPressed(SDLK_LEFT);
                    pressed |= (1 << controllerMap::buttons::FACE_LEFT);
                }
            break;

            case controllerMap::buttons::FACE_DOWN: // Punch.
                if(!(pressed & (1 << controllerMap::buttons::FACE_DOWN))){
                    InputManager::GetInstance().SetKeyPressed(SDLK_DOWN);
                    pressed |= (1 << controllerMap::buttons::FACE_DOWN);
                }
            break;
 
            case controllerMap::buttons::DUP: // Move Up.
                InputManager::GetInstance().SetKeyPressed(SDLK_w);
                break;
            	
            case controllerMap::buttons::DDOWN: // Move Down.
                InputManager::GetInstance().SetKeyPressed(SDLK_s);
            	break;
            
            case controllerMap::buttons::DLEFT: // Move Left.
                InputManager::GetInstance().SetKeyPressed(SDLK_a);
                break;

            case controllerMap::buttons::DRIGHT: // Move Right.
                InputManager::GetInstance().SetKeyPressed(SDLK_d);
            break;

            case controllerMap::buttons::START: // Start level.
				InputManager::GetInstance().SetKeyPressed(SDLK_RETURN);
			break;

            case controllerMap::buttons::SELECT: // Quit level.
				InputManager::GetInstance().SetKeyPressed(SDLK_ESCAPE);
			break;

            case controllerMap::buttons::LDTRIGGER: // Open bend hud and transition level.
				InputManager::GetInstance().SetKeyPressed(SDLK_SPACE);
			break;

            case controllerMap::buttons::RDTRIGGER: // Open and close scroll
				InputManager::GetInstance().SetKeyPressed(SDLK_h);
			break;

            default:
            	std::cout << "default = " << sdlEvent_.cbutton.button << std::endl;
                break;
        }

    }

    // On keyup.
    if(sdlEvent_.type == SDL_CONTROLLERBUTTONUP){

        switch(sdlEvent_.cbutton.button){

        	case controllerMap::buttons::FACE_UP: // Bend key.
				InputManager::GetInstance().SetKeyReleased(SDLK_UP);
				pressed &= ~(1 << controllerMap::buttons::FACE_UP);
			break;

        	case controllerMap::buttons::FACE_DOWN: // Jump and Bend Key.
                InputManager::GetInstance().SetKeyReleased(SDLK_DOWN);
                pressed &= ~(1 << controllerMap::buttons::FACE_DOWN);
            break;

            case controllerMap::buttons::FACE_LEFT: // Punch and Bend key.
                InputManager::GetInstance().SetKeyReleased(SDLK_LEFT);
                pressed &= ~(1 << controllerMap::buttons::FACE_LEFT);
            break;

            case controllerMap::buttons::FACE_RIGHT: // Kick and Bend key.
                InputManager::GetInstance().SetKeyReleased(SDLK_RIGHT);
                pressed &= ~(1 << controllerMap::buttons::FACE_RIGHT);
            break;

            case controllerMap::buttons::DUP: // Move Up.
                InputManager::GetInstance().SetKeyReleased(SDLK_w);
                break;
                
            case controllerMap::buttons::DDOWN: // Move Down.
                InputManager::GetInstance().SetKeyReleased(SDLK_s);
                break;
            
            case controllerMap::buttons::DLEFT: // Move Left.
                InputManager::GetInstance().SetKeyReleased(SDLK_a);
                break;

            case controllerMap::buttons::DRIGHT: // Move Right.
                InputManager::GetInstance().SetKeyReleased(SDLK_d);
            break;

            case controllerMap::buttons::START: // Start level.
				InputManager::GetInstance().SetKeyReleased(SDLK_RETURN);
			break;

			case controllerMap::buttons::SELECT: // Quit level.
				InputManager::GetInstance().SetKeyReleased(SDLK_ESCAPE);
			break;

			case controllerMap::buttons::LDTRIGGER: // Open bend hud and transition level.
				InputManager::GetInstance().SetKeyReleased(SDLK_SPACE);
			break;

			case controllerMap::buttons::RDTRIGGER: // Open and close scroll
				InputManager::GetInstance().SetKeyReleased(SDLK_h);
			break;

            default:
                break;
        }
	}

}
