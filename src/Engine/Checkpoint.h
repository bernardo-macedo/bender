/*
 * Checkpoint.h
 *
 *  Created on: Jul 1, 2015
 *      Author: -Bernardo
 */

#ifndef ENGINE_CHECKPOINT_H_
#define ENGINE_CHECKPOINT_H_

class Checkpoint {
private:
	unsigned int level;
	int posX;

public:
	Checkpoint(unsigned int level, int posX);
	virtual ~Checkpoint();

	unsigned int GetLevel();
	int GetPositionX();
};

#endif /* ENGINE_CHECKPOINT_H_ */
