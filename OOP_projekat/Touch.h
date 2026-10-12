#pragma once

#include "ArgumentCmd.h"

class Touch : public ArgumentCmd {

public:
	using ArgumentCmd::ArgumentCmd;
	virtual void execute() override;
private:
	

	virtual std::string getName() override;
};

inline std::string Touch::getName() { return "touch"; }