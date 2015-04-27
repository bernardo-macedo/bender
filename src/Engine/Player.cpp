/*
 * Player.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: -Bernardo
 */

#include "Player.h"
#include "Constants.h"

Player::Player(float x, float y, Animation* anim) :
	acceleration(0, 0), speed(0,0), onGround(true) {

	sp = new Sprite(Constants::ImgPath + "penguinface.png");
	animation = anim;

	box.SetX(x - animation->GetFrameWidth()/2);
	box.SetY(y - animation->GetFrameHeight()/2);
	box.SetW(animation->GetFrameWidth());
	box.SetH(animation->GetFrameHeight());


	hp = 30;
}

Player::~Player() {
	delete sp;
}

void Player::Update(float dt) {
	acceleration = Point(0, 0);

	if (InputManager::GetInstance().IsKeyDown(A_KEY)) {
		acceleration += Point(-ACCELERATION, 0);
	}
	if (InputManager::GetInstance().IsKeyDown(D_KEY)) {
		acceleration += Point(ACCELERATION, 0);
	}

	if (InputManager::GetInstance().IsKeyDown(S_KEY)) {
		acceleration += Point(0, ACCELERATION);
	}

	// Pulo de tamanho variavel
	if (InputManager::GetInstance().IsKeyDown(SPACEBAR_KEY)) {
		if(state == nochao){
			speed.setY(-JUMP_SPEED_CUT);
			state = caindo;
		}
	}

	Point gravity = Point(0, GRAVITY);
	Point totalForce =  gravity + acceleration;

	speed += (totalForce * dt);
	box.SetX(box.GetX() + (speed.getX() * dt));
	box.SetY(box.GetY() + (speed.getY() * dt));

	speed.setX(speed.getX() * (1.0 - std::min(FRICTION * dt, 1.0)));
	speed.setY(speed.getY() * (1.0 - std::min(FRICTION * dt, 1.0)));

	if (animation != NULL) {
		animation->SetFrameTime(MAX_ANIMATION_TIME - fabs(speed.getX()));
		animation->Update();
	}
}

void Player::Render() {
	//sp->Render(GetBox().GetX() + Camera::pos.getX(), GetBox().GetY() + Camera::pos.getY());
	animation->Render(GetBox().GetX() - Camera::pos.getX(), GetBox().GetY() - Camera::pos.getY());
}

bool Player::IsDead() {
	return hp <= 0;
}

