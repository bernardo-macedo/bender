/*
 * Being.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: -Bernardo
 */

#include "Being.h"

Being::Being(){
	b = NULL;
	scale = 1;
}

Being::~Being() {
	delete b;
}

bool Being::Is(std::string type) {
	return type.compare("Being") == 0;
}

int Being::GetScale() {
	return scale;
}

Body* Being::GetBody() {
	return b;
}
