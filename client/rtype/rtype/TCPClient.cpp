#include "TCPClient.hpp"

TCPClient::TCPClient(std::string const& remote, std::string const& port)
	: _timer(_io_service),
	  _resolver(_io_service),
	  _socket(_io_service),
	  _remote(remote),
	  _port(port)
{
	_connected = false;
}

TCPClient::~TCPClient()
{
}

void TCPClient::connect(void)
{
	StaticTools::Log << "Connecting ..." << std::endl;

	boost::asio::ip::tcp::resolver::query query(_remote, _port);
	boost::asio::ip::tcp::resolver::iterator endpoint_it = _resolver.resolve(query);
	boost::asio::async_connect(_socket, endpoint_it,
		boost::bind(&TCPClient::do_connect, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::iterator));
}

void TCPClient::write(Packet* packet)
{
	bool writeInProgress = !_toWrites.empty();
	_toWrites.push(packet);
	if (!writeInProgress) {
		write();
	}
}

void TCPClient::disconnect(void)
{
	StaticTools::Log << "Disconnecting ..." << std::endl;
	_io_service.stop();
	if (_runThread.joinable()) {
		_runThread.join();
	}
	_connected = false;
	StaticTools::Log << "Disconnected" << std::endl;
}

void TCPClient::run(void)
{
	_runThread = std::thread(&TCPClient::runThread, this);
}

bool TCPClient::isConnected(void) const
{
	return (_connected);
}

IClient &TCPClient::operator<<(Packet *packet)
{
	write(packet);
	return (*this);
}

Packet *TCPClient::createPacket(PacketType type, std::string const& data)
{
	return (StaticTools::CreatePacket(type, data));
}


void TCPClient::read(void)
{
	boost::asio::async_read(_socket, _read.prepare(1024), boost::asio::transfer_at_least(sizeof(Packet)),
		boost::bind(&TCPClient::do_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void TCPClient::write(void)
{
	Packet *packet = _toWrites.front();
	StaticTools::Log << "writing: " << std::string(packet->data, packet->size) << std::endl;
	boost::asio::async_write(_socket, boost::asio::buffer(packet, sizeof(Packet) + packet->size),
	boost::bind(&TCPClient::do_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void TCPClient::do_connect(boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator)
{
	if (!ec) {
		StaticTools::Log << "Connected in TCP mod" << std::endl;
		StaticTools::Log << "Handshaking ..." << std::endl;
	} else {
		_timer.expires_from_now(boost::posix_time::seconds(5));
		_timer.async_wait(boost::bind(&TCPClient::connect, this));
		StaticTools::Log << _remote << ":" << _port << "' is inaccessible (" << ec << ")" << std::endl;
	}
}

void TCPClient::do_read(boost::system::error_code const& ec, size_t len)
{
	if (!ec) {
		Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
		_read.consume(len);

		Packet *reply = NULL;
		_reqHandler.request(*this, packet, &reply);

		if (reply) {
			write(reply);
		}

		if (_connected) {
			read();
		}
	}
	else {
		_connected = false;
		connect();
	}
}

void TCPClient::do_write(boost::system::error_code const& ec, size_t)
{
	if (!ec) {
		Packet *packet = _toWrites.front();
		free(packet);

		_toWrites.pop();
		if (!_toWrites.empty()) {
			write();
		}
	}
}

void TCPClient::runThread(void)
{
	try {
		_io_service.run();
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}