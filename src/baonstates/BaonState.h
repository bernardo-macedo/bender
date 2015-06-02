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

class Body;

class Baon;
class BaonStateManager;

class BaonState {
public:
	virtual ~BaonState();

	virtual void Update(float dt) = 0;
	virtual void NotifyTileCollision(Body* previousBody, float dt) = 0;
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
	Timer *t;
};

#endif /* BAONSTATE_H_ */
