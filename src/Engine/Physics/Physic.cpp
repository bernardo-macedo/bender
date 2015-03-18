/*
 * Physic.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "Physic.h"
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

void Physic::UpdatePhysic(Body* b){
	int count = 0;
	if(!(b->GetForces()).empty()){
		Force* resulting = new Force("result", 0, 0);
		for(Force* f : (b->GetForces())){
			//Force* f = (Force*)*i;
			resulting->SetX(resulting->GetX() + f->GetX());
			resulting->SetY(resulting->GetY() + f->GetY());
		}
		b->setAccelX(resulting->GetX());
		b->setAccelY(resulting->GetY());

		b->SetAngularVel(b->GetAngularVel() + b->GetAngularAccel());
		b->setRotation(b->getRotation() + b->GetAngularVel());
	}

	b->setVelX(b->getVelX() + b->getAccelX());
	b->setVelY(b->getVelY() + b->getAccelY());
	b->setX(b->getX() + b->getVelX());
	b->setY(b->getY() + b->getVelY());

	b->setAccelX(0);
	b->setAccelY(0);
}

Physic* Physic::GetInstance(){
	return instance;
}
