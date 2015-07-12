/*
 * BaonControleState.h
 *
 *  Created on: 11/07/2015
 *      Author: Pedro2
 */

#ifndef BAONSTATES_BAONCONTROLESTATE_H_
#define BAONSTATES_BAONCONTROLESTATE_H_

#include <string>

#include "BaonState.h"
#include "../ControleBend.h"

class BaonControleState : public BaonState{
public:
	BaonControleState(bool flipped);
	~BaonControleState();

	void Update_(float dt);
	void NotifyTileCollision();
	bool Is(std::string state);
private:
	ControleBend *pedra;
};

#endif /* BAONSTATES_BAONCONTROLESTATE_H_ */
