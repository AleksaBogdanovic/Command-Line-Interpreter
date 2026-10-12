#pragma once

#include "OptionalArgumentCmd.h"

class Tr :public OptionalArgumentCmd {
public:
	Tr(Stream* stream, string what, string with);
	Tr(Stream* stream, string what);


	virtual void execute() override;

private:
	virtual std::string getName() override;

	string what;
	string with;
};

inline std::string Tr::getName() { return "tr"; }