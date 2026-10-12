#pragma once

#include "ArgumentCmd.h"
#include "Parser.h"


class Batch : public ArgumentCmd {
public:
	Batch(string argument, Parser* p);
	Batch(string argument, string outFilename, Parser* p);
	virtual void execute() override;

private:

	virtual std::string getName() override;

	Parser* parser;
	string outFilename;
};

inline std::string Batch::getName() { return "batch"; }