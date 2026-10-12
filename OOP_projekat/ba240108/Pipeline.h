#pragma once

#include "Command.h"


class Pipeline : public Command {

public:

	Pipeline(vector<Command*> commands);

	~Pipeline();

	virtual void execute() override;

private:

	virtual std::string getName() override;

	vector<Command*> commands;
};

inline std::string Pipeline::getName() { return "Pipeline"; }
