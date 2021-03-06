#pragma once

#include "ANPC.hpp"
#include "Explosion.hpp"
#include "Powdered.hpp"
#include "Laser.hpp"
#include "LoadedPowdered.hpp"

#include "APowerUp.hpp"
#include "Force.hpp"
#include "DoubleLaser.hpp"

class Mate : public ANPC
{
private:
	static const uint8_t FRAME_TOP;
	static const uint8_t FRAME_MID;
	static const uint8_t FRAME_BOT;
	static const uint8_t FRAME_EXP;

public:
	Mate(void);
	virtual ~Mate(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);
	virtual void move(float delta);

	virtual void shoot(Fire const& param);
	virtual void setPowder(PowderType powderType);

	virtual void respawn(void);

private:
	void initFrame(void);
	void updateFrame(void);

	void collisionDestruction(void);
	void collisionPowerUp(AEntity *other);

	void refreshInvincibility(float delta);

private:
	float _delta;
	bool _decrease;
	uint8_t _targetFrame;
	uint8_t _currentFrame;

	std::unordered_map<uint8_t, sf::IntRect> _frames;
	uint8_t _currentDirection;
	std::pair<short, short> _resolution;

	Powdered *_powder;
	LoadedPowdered *_loadedPowder;
	bool _loadedShot;
	float _deltaInvincibleAnim;
	bool _invincibleAnimState;

	std::list<APowerUp *> _drawablePowerUps;
	Force *_force;
};
