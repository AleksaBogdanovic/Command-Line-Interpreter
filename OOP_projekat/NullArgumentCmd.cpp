#include <iostream>
#include <ctime>
#include <sstream>
#include <string>

#include "NullArgumentCmd.h"


NullArgumentCommand::NullArgumentCommand()
{ }

NullArgumentCommand::NullArgumentCommand(Stream* stream)
	: stream(stream)
{ }

void NullArgumentCommand::makeDateTimeObject(std::tm& t){
	
	std::time_t currentTime = time(nullptr);
	localtime_s(&t, &currentTime);
}


Time::Time()
{ }


void Time::execute(){
	ostream* output = this->stream->getOutputStream();

	std::tm t{};
	makeDateTimeObject(t);

	stringstream result;
	result << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec;

	*output << result.str();
	output->flush();
}

Date::Date()
{}

void Date::execute(){
	ostream* output = this->stream->getOutputStream();

	std::tm t{};
	makeDateTimeObject(t);

	stringstream result;

	//tm_year daje godinu kao broj godina od 1900-te
	result << t.tm_mday << "." << t.tm_mon + 1 << "." << t.tm_year + 1900;

	*output << result.str();
	output->flush();
}
