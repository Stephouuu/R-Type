#pragma once

#include "IRequest.hpp"

class RequestMove : public IRequest
{
public:
	RequestMove(void);
	virtual ~RequestMove(void);

	virtual void execute(std::shared_ptr<AConnection> owner,
		   				 std::shared_ptr<ICommand> received,
						 std::shared_ptr<ICommand> &reply);
};

