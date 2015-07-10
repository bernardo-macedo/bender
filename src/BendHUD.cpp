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
	this->scale = scale;
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
		activeTime[i] = new Timer();
	}
	Hide();
}

BendHUD::~BendHUD() {
}

void BendHUD::Update(float dt){
	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
		activeHide[Arrows::UP] = true;
	}
	if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		activeHide[Arrows::RIGHT] = true;
	}
	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
		activeHide[Arrows::DOWN] = true;
	}
	if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		activeHide[Arrows::LEFT] = true;
	}

	for (int i = 0; i <= 3; ++i) {
		if(activeHide[i]){
			activeTime[i]->Update(dt);
			if (activeTime[i]->Get() > 0.05) {
				activeTime[i]->Restart();
				activeHide[i] = false;
			}
		}
	}
}

void BendHUD::Render(){
	sp->Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0);
	if(activeHide[Arrows::UP]){
		active[Arrows::UP]->Render(box.GetX() + 45 + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), 0);
	}
	if(activeHide[Arrows::RIGHT]){
		active[Arrows::RIGHT]->Render(box.GetX() + 168 + Camera::pos.getX(), box.GetY() + 45 + Camera::pos.getY(), 0);
	}
	if(activeHide[Arrows::DOWN]){
		active[Arrows::DOWN]->Render(box.GetX() + 45 + Camera::pos.getX(), box.GetY() + 168 + Camera::pos.getY(), 0);
	}
	if(activeHide[Arrows::LEFT]){
		active[Arrows::LEFT]->Render(box.GetX() + Camera::pos.getX(), box.GetY() + 45 + Camera::pos.getY(), 0);
	}
}

void BendHUD::NotifyCollision(GameObject* other){}
void BendHUD::NotifyTileCollision(){}

bool BendHUD::IsDead(){
	return isHidden;
}

bool BendHUD::Is(std::string type) {
	return type.compare("BendHUD") == 0;
}

int BendHUD::GetScale() {
	return scale;
}

void BendHUD::Hide() {
	isHidden = true;
	for (int i = 0; i <= 3; ++i) {
		active[i]->SetScaleX(scale);
		active[i]->SetScaleY(scale);
		activeHide[i] = false;
		activeTime[i]->Restart();
	}
}

void BendHUD::Show() {
	isHidden = false;
}
