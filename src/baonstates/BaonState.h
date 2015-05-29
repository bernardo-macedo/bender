/*
 * BaonState.h
 *
 *  Created on: 26/05/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATE_H_
#define BAONSTATE_H_

#include <string>

class Body;

class Baon;
class BaonStateManager;

class BaonState {
public:
	virtual ~BaonState();

	virtual void Update(float dt) = 0;
	virtual void NotifyTileCollision(Body* previousBody, float dt) = 0;
	BaonState* Next();
	void SetNext(BaonState* next);
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

	virtual bool Is(std::string state) = 0;
protected:
	Baon* baon;
	BaonStateManager* sm;
	BaonState *next;
	bool nextRequested, popRequested, flipped, executed;
};

#endif /* BAONSTATE_H_ */