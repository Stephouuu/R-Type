#pragma once

#include <SFML/Graphics.hpp>

class AEntity : public sf::Drawable, public sf::Transformable
{
public:
	AEntity(void);
	virtual ~AEntity(void);

	/* Callback utilis� par World pour init l'objet */
	virtual void init(void) = 0;

	/* Callback utilis� par World pour update l'objet */
	virtual void update(float delta) = 0;

	/* Callback utilis� par World pour d�truire l'objet */
	virtual void destroy(void) = 0;

	/* A appeler quand on souhaite que l'objet soit d�truit */
	void recycle(void);

	/* Retourne true si l'objet va �tre d�truit, sinon false */
	bool isWaitingForRecycle(void) const;

	/* Set une nouvelle forme */
	void setShape(sf::Shape *shape);

	/* Set une nouvelle texture */
	void setTexture(sf::Texture *texture);

private:
	/* Callback utilis� par World pour dessiner l'objet */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/* La forme */
	sf::Shape *_shape;

	/* La texture */
	sf::Texture *_texture;

	/* cf. isWaitingForRecycle() */
	bool _waitingForRecycle;
};

