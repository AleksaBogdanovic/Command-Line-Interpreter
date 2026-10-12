#pragma once

#include "ArgumentCmd.h"

class Truncate :public ArgumentCmd {
public:
	using ArgumentCmd::ArgumentCmd;

	virtual void execute() override;

private:
	virtual std::string getName() override;
};

inline std::string Truncate::getName() { return "truncate"; }