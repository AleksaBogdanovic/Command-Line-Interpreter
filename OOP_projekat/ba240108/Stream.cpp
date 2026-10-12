#include "Stream.h"
#include "Parser.h"
#include <fstream>

using namespace std;

struct Token;

Stream::Stream(istream* input, ostream* output)
	:	input(input)
	,	output(output)
{ }

Stream::Stream(std::ostream * output)
    :   input(nullptr)
    ,   output(output)
{ }

Stream* Stream::createStreamProto(const vector<Token>& tokens, string name) {
    istream* input = nullptr;
    ostream* output = nullptr;

    for (int i = 1; i < tokens.size(); i++) // tokens[0] je ime komande 
    {
        switch (tokens[i].kind) {
        case TokenType::Word:
            if (input) { break; } //prvi word token na koji se naidje je argument, ostalo moze biti deo komande
            inputFileStream(input, tokens[i].value, name);
            break;
        case TokenType::QuotedString:
            if (input) {} //GRESKA
            inputArgumentStream(input, tokens[i].value, name);
            break;
        case TokenType::RedirectInput:
            if (input) {} //GRESKA
            inputFileStream(input, tokens[i].value, name);
            break;
        case TokenType::RedirectOutput:
            if (output) {} //GRESKA
            outputFileStream(output, tokens[i].value, std::ios::out, name);
            break;
        case TokenType::DoubleRedirectOutput:
            if (output) {} //GRESKA
            outputFileStream(output, tokens[i].value, std::ios::app, name);
            break;
        default:
            break;
        }
    }

    if (!input) {
        noArgumentStream(input);
    }
    if (!output) {
        output = &cout;
    }

    return new Stream(input, output);
}

Stream* Stream::createStream(const vector<Token>& tokens, int from, const Token& argument, ostream* defaultOutput, const string& cmd_name){
    istream* input = nullptr;
    ostream* output = nullptr;

    Stream::validateRestofStream(tokens, from, cmd_name);

    if (argument.kind != TokenType::None) {

        if (argument.kind == TokenType::QuotedString) {
            inputArgumentStream(input, argument.value, cmd_name);
        }
        if (argument.kind == TokenType::Word) {
            inputFileStream(input, argument.value, cmd_name);
        }
    }
    
    Stream::searchSetRedirection(tokens, from, input, output, cmd_name);

    if (!output) {
        output = defaultOutput;
    }

    return new Stream(input, output);
}

Stream* Stream::createStream(const vector<Token>& tokens, int from, ostream* defaultOutput, const string& cmd_name){
    istream* input = nullptr;
    ostream* output = nullptr;

    Stream::validateRestofStream(tokens, from, cmd_name);

    Stream::searchSetRedirection(tokens, from, input, output, cmd_name);

    if (!output) {
        output = defaultOutput;
    }

    return new Stream(output);
}

void Stream::searchSetRedirection(const vector<Token>& tokens, int from, istream*& input, ostream*& output, const string& cmd_name){

    for (int i = from; i < tokens.size(); i++)
    {
        Token t = tokens[i];
        switch (t.kind) {
        case TokenType::RedirectInput:
            if (input) Exception::multipleInputSources(cmd_name);
            if (++i == tokens.size() ||  
                tokens[i].kind != TokenType::Word)  Exception::missingRedirectionArgument(cmd_name, t);

            inputFileStream(input, tokens[i].value, cmd_name);
            break;
        case TokenType::RedirectOutput:
            if (output) Exception::multipleOutputSources(cmd_name);
            if (++i == tokens.size() ||
                tokens[i].kind != TokenType::Word)  Exception::missingRedirectionArgument(cmd_name, t);

            outputFileStream(output, tokens[i].value, std::ios::out, cmd_name);
            break;
        case TokenType::DoubleRedirectOutput:
            if (output) Exception::multipleOutputSources(cmd_name);
            if (++i == tokens.size() ||
                tokens[i].kind != TokenType::Word)  Exception::missingRedirectionArgument(cmd_name, t);

            outputFileStream(output, tokens[i].value, std::ios::app, cmd_name);
            break;
        default:
            break;
        }
    }

}


void Stream::inputFileStream(istream*& input, const string& filename, const string& cmd_name)
{
    input = new ifstream(filename);
    if (!*input) Exception::unableToOpenFile(cmd_name, filename);
}

void Stream::outputFileStream(ostream*& output, const string& filename, std::ios_base::openmode mode, const string& cmd_name)
{
    output = new ofstream(filename, mode);
    if (!*output) Exception::unableToOpenFile(cmd_name, filename);
}

void Stream::inputArgumentStream(istream*& input, const string& argument, const string& cmd_name)
{
    stringstream* ss = new stringstream;
    *ss << argument;
    cin.clear(); //ocisti buffer zbog EOF

    input = ss;
}


void Stream::noArgumentStream(istream*& input)
{
    stringstream* ss = new stringstream;

    string str;
    while (getline(cin, str)) {
        *ss << str << '\n';
    }
    cin.clear(); //ocisti buffer zbog EOF
    input = ss;

}

void Stream::validateRestofStream(const vector<Token>& tokens, int from, string name){
    bool previous_redirect = false;
    for (int i = from; i < tokens.size(); i++)
    {
        Token t = tokens[i];
        if (t.kind == TokenType::RedirectInput
            || t.kind == TokenType::DoubleRedirectOutput
            || t.kind == TokenType::RedirectOutput)
        {
            previous_redirect = true;
        }
        else {
            if (previous_redirect) {
                previous_redirect = false;
            }
            else {
                Exception::unexpectedArgument(name, t);
            }

        }
    }

}


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
