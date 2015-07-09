#include "BaonState.h"

std::string BaonState::Next(){
	return next;
}

BaonState::BaonState() {
	t = NULL;
	stateChanged = false;
	bendTimer = new Timer();
	bendTimer->Restart();
	for (int i = 0; i < 4; ++i){
		bendKey[i] = -1;
	}
	countBend = 0;
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

void BaonState::Update(float dt) {
	if(baon->GetBendMode()){
		bendTimer->Update(dt);
		baon->bendHUD->isHide = false;
		if(InputManager::GetInstance().KeyPress(H_KEY)){
			bendKey[countBend] = 0;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(J_KEY)){
			bendKey[countBend] = 1;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(K_KEY)){
			bendKey[countBend] = 2;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(L_KEY)){
			bendKey[countBend] = 3;
			countBend++;
		}
		if(bendKey[0] == 1 && bendKey[1] == 2 && bendKey[2] == 3){
			stateChanged = true;
			baon->SetBendMode(false);
			executed = true;
			nextRequested = true;
			countBend = 0;
			next = "ATTACK1";
			nextFlipped = flipped;
			baon->bendHUD->isHide = true;
			for (int i = 0; i < 4; ++i){
				bendKey[i] = -1;
			}
		}
		if(bendKey[2] == 1 && bendKey[1] == 2 && bendKey[0] == 3){
			stateChanged = true;
			baon->SetBendMode(false);
			executed = true;
			nextRequested = true;
			countBend = 0;
			next = "SPIKESTONE";
			nextFlipped = flipped;
			baon->bendHUD->isHide = true;
			for (int i = 0; i < 4; ++i){
				bendKey[i] = -1;
			}
		}
		if(InputManager::GetInstance().KeyRelease(F_KEY) || bendTimer->Get() > 3 ||countBend >= 3){
			countBend = 0;
			stateChanged = true;
			baon->SetBendMode(false);
			baon->bendHUD->isHide = true;
			for (int i = 0; i < 4; ++i){
				bendKey[i] = false;
			}
		}
	}
	if(!stateChanged){
		Update_(dt);
	}
	stateChanged = false;

}
