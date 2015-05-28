#include "BaonState.h"

BaonState* BaonState::Next(){
	return next;
}
BaonState::~BaonState(){
}
bool BaonState::NextRequested(){
	return nextRequested;
}

bool BaonState::PopRequested(){
	return popRequested;
}

void BaonState::SetPopRequested(bool popRequested) {
	this->popRequested = popRequested;
}

void BaonState::SetNextRequested(bool nextRequested) {
	this->nextRequested = nextRequested;
}

bool BaonState::IsFlipped(){
	return flipped;
}

void BaonState::SetNext(BaonState* next){
	this->next = next;
}

void BaonState::SetFlipped(bool flipped){
	this->flipped = flipped;
}

void BaonState::SetExecuted(bool executed) {
	this->executed = executed;
}

void BaonState::Reset() {
	executed = false;
	nextRequested = false;
}
