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
		if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
			bendKey[countBend] = Arrows::UP;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
			bendKey[countBend] = Arrows::RIGHT;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
			bendKey[countBend] = Arrows::DOWN;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
			bendKey[countBend] = Arrows::LEFT;
			countBend++;
		}

		VerifyAttackOne();

		if(InputManager::GetInstance().KeyRelease(SPACE_KEY) || bendTimer->Get() > 3 ||countBend >= 3){
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

void BaonState::VerifyAttackOne() {
	if(bendKey[0] == Arrows::DOWN && bendKey[1] == Arrows::LEFT && bendKey[2] == Arrows::UP) {
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
}
