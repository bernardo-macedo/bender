/*
 * MyState.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "MyState.h"

MyState::~MyState(){

}

void MyState::Setup(){
	Drone* d = new Drone("teste", 0, 0);
	d->setAccelY(0.9f);
	d->setVelX(3);
	this->Add(d);
}

void MyState::OnRender(){

}

