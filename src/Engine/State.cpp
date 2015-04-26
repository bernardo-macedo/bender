/*
 * State.cpp
 *
 *  Created on: 13/03/2015
 *      Author: Pedro
 */

#include <cstdlib>
#include <ctime>

#include "State.h"
#include "InputManager.h"
#include "Game.h"
#include "Constants.h"

State::State() {
	tileSet = new TileSet(64, 64, Constants::ImgPath + "testTileset.png");
	tileMap = new TileMap(Constants::MapPath + "testMap.txt", tileSet);
	quitRequested = false;
	bg = new Sprite(Constants::ImgPath + "ocean" + Constants::ImgExtension);
	srand(time(NULL));

	// TODO: ao inves de iniciar o personagem aqui, ler posicao dele do tileMap
	// perimitindo que o mapa configure a posicao inicial do player.
	player = new Player(400, 300, new Animation(Constants::ImgPath + "testeAnimacao.png", 64, 64, 200, true));

	//Camera::Follow(player);

}

State::~State(){
	objectArray.clear();
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Update(float dt) {
	int mouseX, mouseY;
	bool achouFace = false;

	// atualiza posicao da camera
	Camera::Update(dt);
	if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}

	// atualiza estado das entidades
	player->Update(dt);
	// testa colisoes
	tileMap->CheckCollision(player);

	/*
	mouseX = InputManager::GetInstance().GetMouseX();
	mouseY = InputManager::GetInstance().GetMouseY();


	for (int i = objectArray.size() - 1; i >= 0; --i) {
		(objectArray[i])->Update(dt);
	}


	if(InputManager::GetInstance().MousePress(1)){
		for(int i = objectArray.size() - 1; i >= 0; --i) {
			Face* face = (Face*) objectArray[i].get();

			if(face->GetBox().IsInside((float)(mouseX - camera->pos.getX()), (float)(mouseY - camera->pos.getY()))) {
				achouFace = true;
				face->Damage((rand() % 10 + 10));
				break;
			}
		}
		if(!achouFace){
			AddObject(mouseX - camera->pos.getX(), mouseY - camera->pos.getY());
		}
	}


	if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
		camera->pos.setX(camera->pos.getX() - 200*Game::GetInstance()->GetDeltaTime());
	}

	if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
		camera->pos.setX(camera->pos.getX() + 200*Game::GetInstance()->GetDeltaTime());
	}

	if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
		camera->pos.setY(camera->pos.getY() + 200*Game::GetInstance()->GetDeltaTime());
	}

	if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
		camera->pos.setY(camera->pos.getY() - 200*Game::GetInstance()->GetDeltaTime());
	}
	*/
}

void State::Render() {
	bg->Render(0, 0);
	tileMap->Render(0, 1, Camera::pos.getX(), Camera::pos.getY());



	/*
	for(unsigned int i = 0; i < objectArray.size(); i++) {
		if((objectArray[i])->IsDead()){
			objectArray.erase(objectArray.begin() + i);
		}
		else{
			objectArray[i]->Render();
		}
	}
	*/
	tileMap->Render(1, 1, Camera::pos.getX(), Camera::pos.getY());

	player->Render();
}

void State::AddObject(float mouseX, float mouseY){
	objectArray.emplace_back(new Player(mouseX, mouseY));
}
