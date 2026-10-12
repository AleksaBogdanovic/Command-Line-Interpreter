#pragma once

#include "Stream.h"
#include "OptionalArgumentCmd.h"


class Echo : public OptionalArgumentCmd
{
public:

	Echo(const string& argument);
	Echo(Stream* stream);

	virtual void execute() override;

private:
	virtual std::string getName() override;
};

inline std::string Echo::getName() { return "echo"; }