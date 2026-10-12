#pragma once

#include "Command.h"
#include <vector>

enum class TokenType {
	Word,
	QuotedString
};

constexpr char OPTION_CHARACTER = '-';

struct Token {

	TokenType kind;
	string value;

	Token(TokenType t)	:kind(t) { }
	Token(TokenType t, string val)	:kind(t), value(val) { }
};

class Parser {
public:
	Command* parseCommand(string line);

private:
	Stream* createStream(Token argument, string name);  // kreiraj stream za komandu kada argument postoji
	Stream* createStream();   // kreiraj stream za komandu kada argument ne postoji
	Stream* argumentStream(const Token& argument, string name); // kreiraj stream za komandu kada argument postoji
	Stream* withoutArgumentStream();

	vector<Token> tokenize(string line);
	string readQuoted(const string& line, int& i); // helper funkcija za tokenize
	string readWord(const string& line, int& i);  // helper funkcija za tokenize
	//Token findArgument(const vector<Token>& tokens); // helper funkcija za createStream

	Command* parseNullArgumentCmd(const vector<Token>& tokens);
	Command* parseArgumentCmd(const vector<Token>& tokens);
	Command* parseOptionalArgumentCmd(const vector<Token>& tokens);


	Command* makeEcho(const vector<Token>& tokens);
	Command* makeWc(const vector<Token>& tokens);
};



//Token Parser::findArgument(const vector<Token>& tokens)
////format funkcije je takav da se argument nalazi ili nakon naziva komande
//// ili kao treca rec
//{
//	return Token(TokenType::QuotedString, "proba");
//}

