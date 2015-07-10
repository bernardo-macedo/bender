#include "StateEnemy.h"

StateEnemy::StateEnemy(Enemy* const enemy_) :
	enemy(enemy_)
{
	askEnd = false;
}

StateEnemy::~StateEnemy(){
	this->enemy = nullptr;
}

bool StateEnemy::AskEnd() {
	return askEnd;
}
