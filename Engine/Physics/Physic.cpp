/*
 * Physic.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "Physic.h"
#include "math.h"
using namespace std;
Physic* Physic::instance = NULL;
Physic::Physic(){
	if(instance == NULL){
		instance = this;
	}
}

Physic::~Physic() {
	// TODO Auto-generated destructor stub
}

void Physic::UpdatePhysic(Body* b, float dt){
	if(!(b->GetForces()).empty()){
		Force* resulting = new Force("result", 0, 0);
		for(Force* f : (b->GetForces())){
			resulting->SetX(resulting->GetX() + f->GetX());
			resulting->SetY(resulting->GetY() + f->GetY());
		}
		b->SetAccelX(resulting->GetX());
		b->SetAccelY(resulting->GetY());
	}

	b->SetAngularVel(b->GetAngularVel() + b->GetAngularAccel()*dt);
	b->SetAngularVel(b->GetAngularVel());
	b->SetRotation(b->GetRotation() + b->GetAngularVel()*dt);

	if(sqrt(pow(b->GetVelX() + b->GetAccelX()*dt,2) + pow(b->GetVelY() + b->GetAccelY()*dt, 2)) <= fabs(b->GetSpeedLimit())){
		b->SetVelX(b->GetVelX() + b->GetAccelX()*dt);
		b->SetVelY(b->GetVelY() + b->GetAccelY()*dt);
	}
	b->SetVelX(b->GetVelX()/b->GetResistance());
	b->SetVelY(b->GetVelY()/b->GetResistance());

	b->SetX(b->GetX() + b->GetVelX()*dt);
	b->SetY(b->GetY() + b->GetVelY()*dt);

	b->SetAccelX(0);
	b->SetAccelY(0);
}

Physic* Physic::GetInstance(){
	return instance;
}
