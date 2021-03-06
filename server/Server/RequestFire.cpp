#include "RequestFire.hpp"
#include "Party.hpp"

RequestFire::RequestFire(void)
{
}

RequestFire::~RequestFire(void)
{
}


void RequestFire::execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply)
{
	(void)reply;
	std::shared_ptr<Party> party = owner->getCurrentParty();

	if (party) {
		party->fire(received);
	}
}