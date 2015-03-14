/*
 * Physic.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "Physic.h"

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
	b->setVelX(b->getVelX() + b->getAccelX());
	b->setVelY(b->getVelY() + b->getAccelY());
	b->setX(b->getX() + b->getVelX());
	b->setY(b->getY() + b->getVelY());
}

Physic* Physic::GetInstance(){
	return instance;
}

