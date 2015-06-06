/*
 * Being.h
 *
 *  Created on: Jun 5, 2015
 *      Author: -Bernardo
 */

#ifndef BEING_H_
#define BEING_H_

#include <memory>
#include "Engine/Physics/Body.h"
#include "Engine/GameObject.h"

class Being : public GameObject {
public:
	Being();
	virtual ~Being();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void NotifyCollision(GameObject* other) = 0;
	virtual void NotifyTileCollision() = 0;
	virtual bool IsDead() = 0;

	virtual bool Is(std::string type);
	int GetScale();
	Body* GetBody();

protected:
	int scale;
	Body* b;
};

#endif /* BEING_H_ */
