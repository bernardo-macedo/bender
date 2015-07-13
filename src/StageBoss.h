/*
 * StageBoss.h
 *
 *  Created on: Jul 13, 2015
 *      Author: -Bernardo
 */

#ifndef STAGEBOSS_H_
#define STAGEBOSS_H_

#include "AbstractStage.h"

class StageBoss : public AbstractStage {
public:
	StageBoss(int posX = -1);
	virtual ~StageBoss();

	bool OnLevelWon(float dt);
};

#endif /* STAGEBOSS_H_ */
