#include "StaticTools.hpp"

std::ofstream StaticTools::Log;

std::pair<short, short> StaticTools::GetResolution(void)
{
	return (std::make_pair<short, short>(1280, 720));
	//return (std::make_pair<short, short>(1664, 936));
}

CommandType StaticTools::GetPacketType(char const *packet)
{
	return (*(CommandType *)(packet));
}

std::string StaticTools::SerializeLoginServer(std::string const& host, std::string const& pwd)
{
	return (host + ";" + pwd);
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