#pragma once

#include "AShip.hpp"

class ANPC : public AShip
{
public:
	ANPC(void);
	virtual ~ANPC(void);

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(IClient &client) = 0;

	virtual void collision(IClient *client, AEntity *other) = 0;
	virtual void applyCollision(CollisionType type, AEntity *other) = 0;

	virtual void shoot(Fire const& param) = 0;
	virtual void setPowder(PowderType powderType) = 0;
	virtual void respawn(void) = 0;
};

