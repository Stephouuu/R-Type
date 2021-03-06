#pragma once

#include "AEntity.hpp"

class LoadedPowdered : public AEntity
{
public:
	LoadedPowdered(void);
	virtual ~LoadedPowdered(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);
	virtual void move(float delta);

	void setColor(uint16_t color);

private:
	void initFrame(void);
	void updateFrame(void);

	sf::RectangleShape *_shape;
	float _delta;
	uint8_t _currentFrame;
	uint16_t _color;
	std::vector<sf::IntRect> _frames;
};

