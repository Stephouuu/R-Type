#pragma once

#include "ICommand.hpp"
#include "StaticTools.hpp"

class CMDFire : public ICommand
{
public:
	CMDFire(void);
	CMDFire(MissileType type, uint16_t id, uint16_t id_launcher, uint16_t x, uint16_t y,
		     uint8_t velocity, float angle, uint8_t effect, uint8_t level);
	virtual ~CMDFire(void);

	virtual void loadFromMemory(char const *data);
	virtual size_t getSize(void) const;
	virtual CommandType getCommandType(void) const;
	virtual char *getData(void) const;

private:
	Fire *_data;
};

