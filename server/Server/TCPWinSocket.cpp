#include "TCPWinSocket.hpp"

TCPWinSocket::TCPWinSocket(void)
{
	_socket = 0;
	WSAStartup(MAKEWORD(2, 0), &_wsdata);
}

TCPWinSocket::~TCPWinSocket(void)
{
	if (_socket) {
		closesocket(_socket);
	}
	WSACleanup();
}

bool TCPWinSocket::connectFromAcceptedFd(int fd)
{
	_socket = fd;
	return true;
}

int TCPWinSocket::recv(char *buffer, size_t blocksize)
{
	return (::recv(_socket, buffer, blocksize * sizeof(char), 0));
}

bool TCPWinSocket::recv(Buffer &buffer, size_t transferAtLeast)
{
	char buf[1024];
	int read = 0;
	size_t total = 0;

	while (total < transferAtLeast && (read = recv(buf, 1024)) > 0) {
		buffer.reallocate(buf, read);
		total += read;
	}
	return (read > 0);
}

int TCPWinSocket::send(char *data, size_t size)
{
	return (::send(_socket, data, size, 0));
}
