#include "StaticTools.hpp"

#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif

std::ofstream StaticTools::Log;

float StaticTools::musicVolume = 100u;
float StaticTools::soundVolume = 100u;

std::pair<short, short> StaticTools::GetResolution(void)
{
	return (std::make_pair<short, short>(1280, 720));
}

std::string StaticTools::SerializeLoginServer(std::string const& host, std::string const& pwd, std::string const& username)
{
	if (username.empty()) {
		return (host + ";" + pwd);
	}
	else {
		return (username + ";" + host + ";" + pwd);
	}
}

uint32_t StaticTools::SerializePosition(uint16_t x, uint16_t y)
{
	return ((x << 16) | y);
}

void StaticTools::DeserializePosition(uint32_t position, uint16_t &x, uint16_t &y)
{
	x = position >> 16;
	y = position & 0xffff;
}

void StaticTools::SplitString(std::string const& s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss;
	std::string buffer;

	ss.str(s);
	while (std::getline(ss, buffer, delim)) {
		elems.push_back(buffer);
	}
}


void StaticTools::Sleep(unsigned int milliseconds)
{
#ifdef _WIN32
	::Sleep(milliseconds);
#else
	usleep(milliseconds * 100);
#endif
}