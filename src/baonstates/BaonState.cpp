#include "BaonState.h"

std::string BaonState::Next(){
	return next;
}

BaonState::BaonState() {
	t = NULL;
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

void BaonState::SetNext(std::string next){
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
	if(t != NULL){
		t->Restart();
	}
}

void BaonState::SetBaon(Baon* baon) {
	this->baon = baon;
}

void BaonState::SetStateManager(BaonStateManager* sm) {
	this->sm = sm;
}

bool BaonState::GetNextFlipped() {
	return nextFlipped;
}

std::string BaonState::GetID() {
	return id;
}
