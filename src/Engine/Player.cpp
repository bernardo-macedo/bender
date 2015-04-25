/*
 * Player.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#include "Player.h"

Player::Player(float x, float y) {
	sp = new Sprite(Constants::ImgPath + "penguinface.png");
	box.SetX(x - sp->GetWidth()/2);
	box.SetY(y - sp->GetHeight()/2);
	box.SetW(sp->GetWidth());
	box.SetH(sp->GetHeight());
	hp = 30;
}

Player::~Player() {
	delete sp;
}

void Player::Update(float dt) {

	// checa input e enfileira acoes

	// executar acoes pendentes
}

void Player::Render() {
}

bool Player::IsDead() {
	return hp <= 0;
}

