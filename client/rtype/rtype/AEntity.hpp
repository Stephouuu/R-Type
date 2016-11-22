#pragma once

#include "ADrawable.hpp"

class AEntity : public ADrawable
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

private:
	/* cf. isWaitingForRecycle() */
	bool _waitingForRecycle;
};