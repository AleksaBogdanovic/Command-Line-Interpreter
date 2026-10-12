#include "Stream.h"
#include "Parser.h"
#include <fstream>

using namespace std;

struct Token;

Stream::Stream(istream* input, ostream* output)
	:	input(input)
	,	output(output)
{}

string Stream::getLine(){
	string line;
	getline(*input, line);
	return line;
}

bool Stream::isEof(){
	if (input->eof()) {
		input->clear();
		return true;
	}
	return false;
}


ConsoleStream::ConsoleStream()
	: Stream(&cin, &cout)
{}
