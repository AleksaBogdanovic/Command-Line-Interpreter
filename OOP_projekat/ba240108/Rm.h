#pragma once

#include "ArgumentCmd.h"

class Rm :public ArgumentCmd {
public:
	using ArgumentCmd::ArgumentCmd;

	virtual void execute() override;

private:
	virtual std::string getName() override;
};

inline std::string Rm::getName() { return "rm"; }