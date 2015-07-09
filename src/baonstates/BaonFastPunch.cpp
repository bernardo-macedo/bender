/*
 * BaonFastPunch.cpp
 *
 *  Created on: 01/07/2015
 *      Author: Pedro2
 */

#include "BaonFastPunch.h"

#include <string>

#include "../Baon.h"
#include "../Engine/Physics/Body.h"
#include "../Engine/Physics/Force.h"

BaonFastPunch::BaonFastPunch(bool flipped) : BaonState(){
	executed = false;
	nextRequested = false;
	this->flipped = flipped;
	t = new Timer();
	fastPunchSound = new Sound("audio/sfx_char_fast_punch.wav");
}

BaonFastPunch::~BaonFastPunch() {
	delete fastPunchSound;
}

void BaonFastPunch::Update_(float dt) {
	if(!executed) {
		fastPunchSound->Play(0);
		baon->GetSprite()->SetFrameHeight(50);
		baon->GetSprite()->SetFrameWidth(50);
		baon->GetSprite()->SetFrameCount(3);
		baon->GetSprite()->SetLine(8, 50);

		if(flipped){
			baon->GetBody()->ApplyForce(new Force("stopping", 700, 0));
		}
		else{
			baon->GetBody()->ApplyForce(new Force("stopping", -700, 0));
		}

		executed = true;
	}
	else{
		if(baon->GetSprite()->GetCurrentFrame() >= 3){
			baon->isDamage = true;
			t->Update(dt);
		}
		else{
			baon->GetSprite()->Update(dt);
		}
		if(t->Get() >= 0.3){
			baon->GetBody()->removeForce("stopping");
			baon->GetBody()->SetVelX(0);
			nextRequested = true;
			nextFlipped = flipped;
			next = "STAND";
			baon->isDamage = false;
		}
	}
}

void BaonFastPunch::NotifyTileCollision() {
}

bool BaonFastPunch::Is(std::string state) {
	return state.compare("FASTPUNCH") == 0;
}
