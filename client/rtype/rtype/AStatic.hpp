#pragma once

#include "AEntity.hpp"

class AStatic : public AEntity
{
public:
	AStatic(void);
	virtual ~AStatic(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(IClient &client) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type, AEntity *other) = 0;

	virtual void move(float delta);
};

