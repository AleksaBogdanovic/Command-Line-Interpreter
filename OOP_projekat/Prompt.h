#pragma once

#include "ArgumentCmd.h"

class Prompt : public ArgumentCmd {

public:
	using ArgumentCmd::ArgumentCmd;

	virtual void execute() override;

	void print();

private:
	virtual std::string getName() override;

	static string prompt;
};

inline std::string Prompt::getName() { return "prompt"; }
