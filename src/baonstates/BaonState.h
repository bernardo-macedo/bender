/*
 * BaonState.h
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATE_H_
#define BAONSTATE_H_

#include <string>

#include "../Engine/Timer.h"
#include "../Engine/InputManager.h"
#include "../BendHUD.h"
#include "../Baon.h"

class Body;
class BaonStateManager;

class BaonState {
public:
	BaonState();
	virtual ~BaonState();

	void Update(float dt);
	virtual void Update_(float dt) = 0;
	virtual void NotifyTileCollision() = 0;
	std::string Next();
	void SetNext(std::string next);
	bool NextRequested();
	bool PopRequested();
	void SetPopRequested(bool popRequested);
	void SetNextRequested(bool nextRequested);
	void SetBaon(Baon* baon);
	void SetStateManager(BaonStateManager* sm);
	bool IsFlipped();
	void SetFlipped(bool flipped);
	void SetExecuted(bool executed);
	void Reset();
	bool GetNextFlipped();
	std::string GetID();

	virtual bool Is(std::string state) = 0;
protected:
	Baon* baon;
	BaonStateManager* sm;
	std::string next, id;
	bool nextRequested, popRequested, flipped, executed, nextFlipped;
	Timer *t, *bendTimer;

	int bendKey[4];
	bool stateChanged;
	BendHUD* bendHUD;
	unsigned int countBend;

private:
	enum Arrows {UP, RIGHT, DOWN, LEFT};
	enum BendAttack {SUPERJUMP, SPIKESTONE, NONE};

	BendAttack MatchAttack();
	void ResolveAttack(BendAttack attack);
	void CallAttackState();
};

#endif /* BAONSTATE_H_ */
