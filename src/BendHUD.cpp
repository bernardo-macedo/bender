/*
 * BendHUD.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: Simiao
 */

#include "BendHUD.h"
#include "Engine/Camera.h"
#include "Engine/InputManager.h"
#include <iostream>

BendHUD::BendHUD(int scale){
	scale = scale;
	sp = new Sprite("img/BendingMode/bendinghud.png", 1, 0);
	active[0] = new Sprite("img/BendingMode/activeup.png", 1, 0);
	active[1] = new Sprite("img/BendingMode/activeright.png", 1, 0);
	active[2] = new Sprite("img/BendingMode/activedown.png", 1, 0);
	active[3] = new Sprite("img/BendingMode/activeleft.png", 1, 0);
	box.SetH(sp->GetHeight());
	box.SetW(sp->GetWidth());
	sp->SetScaleX(scale);
	sp->SetScaleY(scale);
	for (int i = 0; i <= 3; ++i) {
		active[i]->SetScaleX(scale);
		active[i]->SetScaleY(scale);
		activeHide[i] = false;
		activeTime[i] = new Timer();
	}
	isHide = true;
}

BendHUD::~BendHUD() {
}

void BendHUD::Update(float dt){
	if(InputManager::GetInstance().KeyPress(H_KEY)){
		activeHide[0] = true;
	}
	if(InputManager::GetInstance().KeyPress(J_KEY)){
		activeHide[1] = true;
	}
	if(InputManager::GetInstance().KeyPress(K_KEY)){
		activeHide[2] = true;
	}
	if(InputManager::GetInstance().KeyPress(L_KEY)){
		activeHide[3] = true;
	}
	for (int i = 0; i <= 3; ++i)
	{
		if(activeHide[i]){
			activeTime[i]->Update(dt);
			if (activeTime[i]->Get() > 0.1)
			{
				activeTime[i]->Restart();
				activeHide[i] = false;
			}
		}
	}
}

void BendHUD::Render(){
	sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0);
	if(activeHide[0]){
		active[0]->Render(box.GetX() + 45 + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0);
	}
	if(activeHide[1]){
		active[1]->Render(box.GetX() + 168 + Camera::pos.getX(), box.GetY() + 45 + Camera::pos.getY(), 0);
	}
	if(activeHide[2]){
		active[2]->Render(box.GetX() + 45 + Camera::pos.getX(), box.GetY() + 168 + Camera::pos.getY(), 0);
	}
	if(activeHide[3]){
		active[3]->Render(box.GetX() + Camera::pos.getX(), box.GetY() + 45 + Camera::pos.getY(), 0);
	}
}

void BendHUD::NotifyCollision(GameObject* other){}
void BendHUD::NotifyTileCollision(){}

bool BendHUD::IsDead(){
	return isHide;
}

bool BendHUD::Is(std::string type) {
	return type.compare("BendHUD") == 0;
}

int BendHUD::GetScale() {
	return scale;
}
