/*
 * Drone.cpp
 *
 *  Created on: 14/03/2015
 *      Author: Pedro
 */

#include "Drone.h"
#include "SDL.h"

int Drone::WIDTH = 60;
int Drone::HEIGHT = 20;

Drone::~Drone() {

}

void Drone::Update(){
	SetColor(red, green - 6, blue, alpha);
}

bool Drone::IsDead(){
	return false;
}
