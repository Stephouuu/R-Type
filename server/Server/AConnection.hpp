#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <functional>
#include <cmath>

#include "ISocket.hpp"
#include "RequestHandler.hpp"
#include "ICommand.hpp"
#include "CMDPing.hpp"

#include "StaticTools.hpp"
#include "ConnectionManager.hpp"
#include "PlayerData.hpp"

class Party;
class PartyManager;

#define EAST 1
#define WEAST 2
#define NORTH 4
#define SOUTH 8

class AConnection : public std::enable_shared_from_this<AConnection>
{
public:
	AConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm);
	~AConnection(void);

	virtual void start(void) = 0;
	virtual void close(void) = 0;

	virtual void write(std::shared_ptr<ICommand> command) = 0;
	virtual void sync_write(std::shared_ptr<ICommand> command) = 0;

	void update(double delta);

	ConnectionManager &getConnectionManager(void);
	PartyManager &getPartyManager(void);
	RequestHandler &getRequestHandler(void);

	void setCurrentParty(std::shared_ptr<Party> party);
	void setID(uint16_t id);
	void setName(std::string const& name);
	void setLife(uint8_t life);
	void setScore(uint16_t score);
	void setRunning(bool value);
	void setReady(bool value);
	void setPosition(double x, double y);
	void setDirection(int direction);
	void setVelocity(float velocity);
	void setAngle(float angle);
	void setEffect(EffectType type, bool toAdd);

	std::shared_ptr<Party> getCurrentParty(void) const;
	std::string const& getName(void) const;
	uint8_t getLife(void) const;
	uint16_t getScore(void) const;
	bool isRunning(void) const;
	bool isReady(void) const;
	float getAngle(void) const;
	float getVelocity(void) const;
	PlayerData const& getPlayerData(void) const;
	bool isEffectPresent(EffectType type) const;

	virtual void do_read(bool error) = 0;
	virtual void do_write(void) = 0;

private:
    ConnectionManager &_cm;
    RequestHandler &_rh;
	PartyManager &_pm;

	std::shared_ptr<Party> _party;
	bool _running;
	//std::pair<double, double> _position;
	bool _ready;

	//uint16_t _id;
	uint8_t _life;
	uint16_t _score;
	std::string _name;
	int _direction;
	float _velocity;
	float _angle;
	float _radians;

	PlayerData _playerData;
	std::set<EffectType> _effects;
};

