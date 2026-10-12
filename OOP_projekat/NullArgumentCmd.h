#pragma once

#include<iostream>
#include "Command.h"

class NullArgumentCommand : public Command {
public:
	NullArgumentCommand();
	NullArgumentCommand(Stream* stream);
	 
	//virtual void execute(Stream* Input, Stream* Output) = 0;
	virtual void execute() = 0;

protected:
	//pomocna funkcija za Date i Time komande
	void makeDateTimeObject(std::tm &t);

	Stream* stream;
private:
	virtual Stream* getStream() override;

	
};


class Time : public NullArgumentCommand{
public:
	Time();
	using NullArgumentCommand::NullArgumentCommand;
	
	virtual void execute() override;

private:
	virtual std::string getName() override;
};


class Date : public NullArgumentCommand {
public:
	Date();
	using NullArgumentCommand::NullArgumentCommand;
	
	virtual void execute() override;

private:
	virtual std::string getName() override;
};

inline std::string Time::getName() { return "time"; }
inline std::string Date::getName() { return "date"; }

inline Stream* NullArgumentCommand::getStream() { return stream; }
