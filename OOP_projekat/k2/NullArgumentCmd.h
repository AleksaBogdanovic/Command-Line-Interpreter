#pragma once

#include<iostream>
#include "Command.h"

class NullArgumentCommand : public Command {
public:
	 
	//virtual void execute(Stream* Input, Stream* Output) = 0;
	virtual void execute() = 0;

protected:
	//pomocna funkcija za Date i Time komande
	void makeDateTimeObject(std::tm &t);
};


class Time : public NullArgumentCommand{
public:
	Time();
	
	virtual void execute() override;

private:
	virtual std::string getName() override;
};


class Date : public NullArgumentCommand {
public:
	Date();

	virtual void execute() override;

private:
	virtual std::string getName() override;
};

inline std::string Time::getName() { return "time"; }
inline std::string Date::getName() { return "date"; }
