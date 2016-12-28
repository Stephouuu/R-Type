#pragma once

#ifdef WIN32
# define MONSTER_API __declspec(dllexport)
#else
# define MONSTER_API
#endif

#include <iostream>
#include <vector>
#include <cmath>

#include "StaticTools.hpp"
#include "IMonster.hpp"

class Gomander : public IMonster
{
public:
	Gomander(void);
	virtual ~Gomander(void);

	virtual void update(double delta, std::vector<PlayerData> const& players);
	virtual void takeDamage(uint8_t damage);

	virtual void setID(uint16_t value);
	virtual void setPosition(std::pair<double, double> const& pos);
	virtual void setAngle(double angle);
	virtual void move(double x, double y);

	virtual State popAction(void);

	virtual uint16_t getID(void) const;
	virtual int getDirection(void) const;
	virtual uint16_t getScoreValue(void) const;
	virtual uint8_t getHP(void) const;
	virtual double getFireRate(void) const;
	virtual uint16_t getVelocity(void) const;
	virtual uint8_t getAngle(void) const;
	virtual std::string getType(void) const;
	virtual std::pair<double, double> const& getPosition(void) const;
	virtual std::vector<std::pair<uint16_t, uint16_t> > const& getCanonRelativePosition(void) const;
	virtual std::vector<float> const& getCanonDegrees(void) const;

private:
	double _delta;
	uint16_t _id;
	uint8_t _life;
	double _fireRate; // en seconde
	uint16_t _velocity;
	std::pair<double, double> _position;
	double _angle; // angle de l'entit�
	double _radians;
	std::vector<std::pair<uint16_t, uint16_t> > _canonsRelativePosition; // positions des canons en relatif � l'entit�
	std::vector<float> _canonsDegrees; // en degr�e (ou radian ?)
	State _state;
	int _direction;
};

extern "C" MONSTER_API IMonster *entry(void)
{
	return (new Gomander);
}

extern "C" MONSTER_API const char *type(void)
{
	return ("Gomander");
}
