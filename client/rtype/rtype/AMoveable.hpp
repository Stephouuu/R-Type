#pragma once

#include "ADestroyable.hpp"

class AMoveable : public ADestroyable
{
public:
	AMoveable();
	virtual ~AMoveable();

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type) = 0;

	virtual void move(float delta);
};

