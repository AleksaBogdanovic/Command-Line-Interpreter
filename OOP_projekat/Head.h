#pragma once

#include "OptionalArgumentCmd.h"

class Head :public OptionalArgumentCmd {
public:
	Head(Stream* stream, int count);


	virtual void execute() override;

private:
	virtual std::string getName() override;

	int count;
};

inline std::string Head::getName() { return "head"; }
