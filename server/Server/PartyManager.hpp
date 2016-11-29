#pragma once

#include <list>

#include "Party.hpp"

class PartyManager
{
public:
	PartyManager(void);
	~PartyManager(void);

	void addParty(std::string name, std::string pwd);
	void removeParty(std::string name, std::string pwd);
	std::shared_ptr<Party> addUser(std::string name, std::string pwd, std::shared_ptr<AConnection> user);

private:
	std::list<std::shared_ptr<Party> > _parties;
};

