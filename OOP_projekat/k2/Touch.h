#pragma once

#include "ArgumentCmd.h"

class Touch : public ArgumentCmd {

public:
	using ArgumentCmd::ArgumentCmd;

private:
	virtual void execute() override;

	virtual std::string getName() override;
};

inline std::string Touch::getName() { return "touch"; }