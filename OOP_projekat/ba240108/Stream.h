#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Token;


class Stream {

public:
	Stream(std::istream* input, std::ostream* output);
	Stream(std::ostream* output);
	static Stream* createStreamProto(const vector<Token>& tokens, string name);
	static Stream* createStream(const vector<Token>& tokens, int from, const Token& argument, ostream* defaultOutput, const string& cmd_name);
	static Stream* createStream(const vector<Token>& tokens, int from, ostream* defaultOutput, const string& cmd_name); //za komande koje nemaju ulaz

	string getLine();
	bool isEof();

	ostream* getDefaultOutput();
	void setDefaultOutput(ostream* os);

	istream* getInputStream();
	ostream* getOutputStream();
	void setInputStream(istream* is);
	void setOutputStream(ostream* os);

	// funkcije namestaju vrednosti za input i output Stream klase
	static void noArgumentStream(istream*& input);
private:
	static void searchSetRedirection(const vector<Token>& tokens, int from, istream*& input, ostream*& output, const string& cmd_name);
	// funkcije namestaju vrednosti za input i output Stream klase
	static void inputFileStream(istream*& input, const string& filename, const string& cmd_name);
	static void outputFileStream(ostream*& output, const string& filename, std::ios_base::openmode mode, const string& cmd_name);
	static void inputArgumentStream(istream*& input, const string& argument, const string& cmd_name);
	
	//proveri da li je su ostale iskljucivo redirekcije
	static void validateRestofStream(const vector<Token>& tokens, int from, string name);

	


	istream* input;
	ostream* output;
	ostream* defaultOutput = &cout;
};


class ConsoleStream : public Stream{

public:

	ConsoleStream();


};

inline std::istream* Stream::getInputStream() { return input ? input : &cin; }

inline std::ostream* Stream::getOutputStream() { return output ? output : defaultOutput; }

inline void Stream::setInputStream(istream* is) { input = is; }

inline void Stream::setOutputStream(ostream* os) { output = os; }




inline ostream* Stream::getDefaultOutput() { return defaultOutput; }

inline void Stream::setDefaultOutput(ostream* os) {
	defaultOutput = os;
}