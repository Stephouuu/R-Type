#pragma once

#include <SFML/Graphics.hpp>

#include "InputHandler.hpp"
#include "ProjectResource.hpp"

class AController
{
public:
	AController();
	virtual ~AController();

	virtual void init(void) = 0;
	virtual bool input(InputHandler &input) = 0;
	virtual void update(float delta) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void recycle(void) = 0;
};

