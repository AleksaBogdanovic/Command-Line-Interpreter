#pragma once

#include "OptionalArgumentCmd.h"

class Wc : public OptionalArgumentCmd{

public:

	Wc(Stream* stream);

	virtual void execute() override;

private:

	virtual int count(istream* input) = 0;

	virtual std::string getName() override;
};

class WcCharacter : public Wc {

public:
	WcCharacter(Stream* stream);
private:
	virtual int count(istream* input) override;
};

class WcWord : public Wc {
public:
	WcWord(Stream* stream);
private:
	virtual int count(istream* input) override;

};

inline std::string Wc::getName() { return "wc"; }