#pragma once

#include "Command.h"
#include <vector>

enum class TokenType {
	Word,
	QuotedString,
	Option,
	RedirectInput,
	RedirectOutput,
	DoubleRedirectOutput,
	Pipe,
	None
};

enum class PipelinePosition {
	START,
	MIDDLE,
	END
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
	Command* parseTokens(const vector<Token>& tokens);
	Command* parsePipeline(const vector<Token>& tokens);

	ostream* getDefaultOutput();
	void setDefaultOutput(ostream* os);
private:




	vector<Token> tokenize(string line);
	string readQuoted(const string& line, int& i); // helper funkcija za tokenize
	string readWord(const string& line, int& i);  // helper funkcija za tokenize, prihvata samo alfanumericke karaktere i '-','_'
												 //  baca gresku u suprotnom

	Command* parseNullArgumentCmd(const vector<Token>& tokens);
	Command* parseArgumentCmd(const vector<Token>& tokens);
	Command* parseOptionalArgumentCmd(const vector<Token>& tokens);


	Command* makeEcho(const vector<Token>& tokens);
	Command* makeWc(const vector<Token>& tokens);
	Command* makeTr(const vector<Token>& tokens);
	Command* makeHead(const vector<Token>& tokens);
	Command* makeBatch(const vector<Token>& tokens);


	//helper funkcije za obradu Pipeline
	bool containsPipe(const vector<Token>& tokens);
	vector<vector<Token>> extractPipelineSegments(const vector<Token>& tokens);
	void validatePipelineSegment(const vector<Token>& segment, PipelinePosition position);


	Token getArgument(const vector<Token>& tokens, int& i);//ukoliko je na poziciji i argument, vraca njegovu vrednost 
														   //u suprotnom vraca None token
	bool validateCount(string num, int& count);


	ostream* defaultOutput = &cout;
};


inline Token Parser::getArgument(const vector<Token>& tokens, int& i)
{
	Token none = Token(TokenType::None);
	if (i >= tokens.size()) return none;
	if (tokens[i].kind == TokenType::Word || tokens[i].kind == TokenType::QuotedString)
		return tokens[i++];
	return none;
}

inline bool Parser::validateCount(string num, int& count){
	if (num[0] != 'n') return false;

	string number = "";
	for (int i = 1; i < num.size(); i++) {
		if (!isdigit(num[i])) return false;
		number.push_back(num[i]);
	}

	if (number.size() > 5) return false;

	count = stoi(number);
	return true;
}

inline bool Parser::containsPipe(const vector<Token>& tokens){
	for (auto t : tokens) 
		if (t.kind == TokenType::Pipe) return true;
	
	return false;
}


inline ostream* Parser::getDefaultOutput() { return defaultOutput; }

inline void Parser::setDefaultOutput(ostream* os){
	defaultOutput = os;
}


