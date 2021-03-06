#pragma once

#include <iostream>
#include <functional>

#include "AConnection.hpp"

#include "ThreadPool.hpp"
#include "ReceiveFromAsyncTask.hpp"
#include "SendToAsyncTask.hpp"

#include "IUDPSocket.hpp"
#include "Endpoint.hpp"

#ifdef _WIN32
# include "UDPWinSocket.hpp"
#else
//# include "UDPUnixSocket.hpp"
#endif

class UDPConnection : public AConnection
{
public:
	static void AsyncReceiveFrom(std::shared_ptr<IUDPSocket> socket, Buffer &buffer, Endpoint &endpoint,
									std::function<void(bool)> callback);

	static void AsyncSendTo(std::shared_ptr<IUDPSocket> socket, Endpoint const& endpoint,
									char *data, size_t size, std::function<void(void)> callback);

public:
	UDPConnection(ConnectionManager &cm, RequestHandler &rh, PartyManager &pm);
	virtual ~UDPConnection(void);

	virtual void start(void);
	virtual void close(void);

	virtual void write(std::shared_ptr<ICommand> command);
	virtual void sync_write(std::shared_ptr<ICommand> command);

private:
	void read(void);
	void write(void);

	virtual void do_read(bool error);
	virtual void do_write(void);

	std::shared_ptr<IUDPSocket> _socket;
	Endpoint _endpoint;
	std::queue<std::shared_ptr<ICommand> > _toWrites;
	Buffer _read;
};

