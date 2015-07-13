#include "BaonState.h"

BaonState::BaonState() {
	t = NULL;
	stateChanged = false;
	bendTimer = new Timer();
	for (int i = 0; i < 4; ++i){
		bendKey[i] = -1;
	}
	countBend = 0;
	nextRequested = false;
	popRequested = false;
	executed = false;
	nextFlipped = false;
	flipped = false;
	bendHUD = NULL;
	baon = NULL;
	sm = NULL;

	bendErrorSound = new Sound("audio/sfx_bend_error.wav");
}

BaonState::~BaonState(){
	delete bendErrorSound;
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

std::string BaonState::Next() {
	return next;
}

void BaonState::Update(float dt) {
	if(baon->GetBendMode()){
		bendTimer->Update(dt);
		baon->bendHUD->Show();
		if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
			baon->GetSprite()->SetFrameWidth(35);
			baon->GetSprite()->SetFrameHeight(50);
			baon->GetSprite()->SetFrameCount(1);
			baon->GetSprite()->SetLine(12, 50);

			bendKey[countBend] = Arrows::UP;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
			baon->GetSprite()->SetFrameWidth(35);
			baon->GetSprite()->SetFrameHeight(50);
			baon->GetSprite()->SetFrameCount(1);
			baon->GetSprite()->SetLine(9, 50);
			bendKey[countBend] = Arrows::RIGHT;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
			baon->GetSprite()->SetFrameWidth(35);
			baon->GetSprite()->SetFrameHeight(50);
			baon->GetSprite()->SetFrameCount(1);
			baon->GetSprite()->SetLine(10, 50);
			bendKey[countBend] = Arrows::DOWN;
			countBend++;
		}
		if(InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
			baon->GetSprite()->SetFrameWidth(35);
			baon->GetSprite()->SetFrameHeight(50);
			baon->GetSprite()->SetFrameCount(1);
			baon->GetSprite()->SetLine(11, 50);
			bendKey[countBend] = Arrows::LEFT;
			countBend++;
		}

		if(InputManager::GetInstance().KeyRelease(SPACE_KEY) || bendTimer->Get() > 0.6 ||countBend >= 3) {
			BendAttack matchedAttack = MatchAttack();

			if (bendTimer->Get() > 0.6 || (countBend >= 3 && matchedAttack == BendAttack::NONE)) {
				bendErrorSound->Play(0);
			}

			ResolveAttack(matchedAttack);

			baon->SetBendMode(false);
			bendTimer->Restart();
			countBend = 0;
			stateChanged = true;
			baon->SetBendMode(false);
			baon->bendHUD->Hide();
			for (int i = 0; i < 4; ++i){
				bendKey[i] = -1;
			}
		}
	}
	if(!stateChanged){
		Update_(dt);
	}
	stateChanged = false;

}

BaonState::BendAttack BaonState::MatchAttack() {
	if(bendKey[0] == Arrows::UP && bendKey[1] == Arrows::DOWN && bendKey[2] == Arrows::UP) {
		return BendAttack::SUPERJUMP;
	}
	if (bendKey[0] == Arrows::LEFT && bendKey[1] == Arrows::DOWN && bendKey[2] == Arrows::RIGHT) {
		return BendAttack::SPIKESTONE;
	}
	if (bendKey[0] == Arrows::DOWN && bendKey[1] == Arrows::LEFT && bendKey[2] == Arrows::UP) {
		return BendAttack::DEFENSE;
	}
	if (bendKey[0] == Arrows::RIGHT && bendKey[1] == Arrows::DOWN && bendKey[2] == Arrows::RIGHT) {
		return BendAttack::CONTROLE;
	}
	return BendAttack::NONE;
}

void BaonState::ResolveAttack(BendAttack attack) {
	switch(attack) {
	case SUPERJUMP:
		next = "ATTACK1";
		break;
	case SPIKESTONE:
		next = "SPIKESTONE";
		break;
	case DEFENSE:
		next = "BENDDEFESA";
		break;
	case CONTROLE:
		next = "BENDCONTROLE";
		break;
	default:
		// Nao deixa chamar CallAttackState caso attack = NONE
		return;
	}

	CallAttackState();
}

void BaonState::CallAttackState() {
	stateChanged = true;
	baon->SetBendMode(false);
	executed = true;
	nextRequested = true;
	countBend = 0;
	nextFlipped = flipped;
	baon->bendHUD->Hide();
	for (int i = 0; i < 4; ++i){
		bendKey[i] = -1;
	}
}
