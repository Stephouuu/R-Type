#pragma once

#include <unordered_map>

#include "AProjectile.hpp"
#include "Explosion.hpp"
#include "World.hpp"

class Laser : public AProjectile
{
public:
	Laser(void);
	virtual ~Laser(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);

	void setColor(uint16_t color);
	void setLoadedTiming(float delta);

	sf::Vector2f getSpriteSize(void) const;

private:
	void initFrame(void);
	void updateFrame(void);

private:
	sf::RectangleShape *_shape;

	float _delta;
	uint8_t _currentFrame;
	uint16_t _color;
	std::unordered_map<uint8_t, sf::IntRect[2]> _frames;
	bool _toRecycle;
};

