#pragma once

#include <iostream>
#include <sstream>

using namespace std;

struct Token;


class Stream {

public:


	Stream(std::istream* input, std::ostream* output);

	string getLine();
	bool isEof();

	virtual istream* getInputStream();

	virtual ostream* getOutputStream();

private:
	istream* input;
	ostream* output;
};

inline std::istream* Stream::getInputStream() { return input; }

inline std::ostream* Stream::getOutputStream() { return output; }




class ConsoleStream : public Stream{

public:

	ConsoleStream();


};