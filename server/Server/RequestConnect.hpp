#pragma once

#include "IRequest.hpp"

class RequestConnect : public IRequest
{
public:
	RequestConnect(void);
	virtual ~RequestConnect(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
						 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

