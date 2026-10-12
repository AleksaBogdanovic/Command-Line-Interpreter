#pragma once

#include "Command.h"

class OptionalArgumentCmd : public Command
{
public:
	//mozda napraviti poseban konstruktor koji se zove bez argumenta
	OptionalArgumentCmd(const string& argument);
	OptionalArgumentCmd(Stream* stream);

	~OptionalArgumentCmd();

protected:
	Stream* stream;
};
