#include "AExplosion.hpp"

AExplosion::AExplosion()
	: _delta(0),
	  _currentFrame(0),
	  _maxFrame(0)
{
	setCollisionType(COLLISION_NONE);
}

AExplosion::~AExplosion(void)
{
}


void AExplosion::update(float delta)
{
	_delta += delta;
	if (_delta > 0.01f) {
		if (_currentFrame != _maxFrame - 1) {
			++_currentFrame;
		}
		else {
			recycle();
		}
		getShape()->setTextureRect(sf::IntRect((_currentFrame % _matrixSize.x) * _cellSize.x,
			(_currentFrame / _matrixSize.x) * _cellSize.y, _cellSize.x, _cellSize.y));
		_delta = 0.f;
	}
}

void AExplosion::move(float delta)
{
	(void)delta;
}

void AExplosion::collision(IClient *client, AEntity *other)
{
	(void)client;
	(void)other;
}

void AExplosion::applyCollision(CollisionType type, AEntity *other)
{
	(void)type;
	(void)other;
}

void AExplosion::setTextureSize(sf::Vector2i const& size)
{
	_textureSize = size;
}

void AExplosion::setMatrixSize(sf::Vector2i const& size)
{
	_matrixSize = size;
	_maxFrame = size.x * size.y;
}

void AExplosion::computeCellSize(void)
{
	_cellSize.x = _textureSize.x / _matrixSize.x;
	_cellSize.y = _textureSize.y / _matrixSize.y;
}