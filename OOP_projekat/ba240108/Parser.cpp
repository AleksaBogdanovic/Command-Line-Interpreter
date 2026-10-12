#include "Parser.h"
#include "NullArgumentCmd.h"
#include "Touch.h"
#include "Echo.h"
#include "Wc.h"
#include "Prompt.h"
#include "Truncate.h"
#include "Rm.h"
#include "Tr.h"
#include "Head.h"
#include "Batch.h"
#include "Pipeline.h"
#include "Exceptions.h"

Command* Parser::parseCommand(string line){
    vector<Token> tokens = tokenize(line);

    if (containsPipe(tokens)) return parsePipeline(tokens);

    return parseTokens(tokens);
}

Command* Parser::parseTokens(const vector<Token>& tokens)
{
    if (tokens.empty()) Exception::emptyCommand();

    Token cmd = tokens[0];
    if (cmd.kind != TokenType::Word) Exception::badTypeCommand();
    string cmd_name = cmd.value;

    if (cmd_name == "time" || cmd_name == "date") {
        return parseNullArgumentCmd(tokens);
    }

    if (cmd_name == "touch" || cmd_name == "prompt" ||
        cmd_name == "truncate" || cmd_name == "rm" || cmd_name == "batch") {
        return parseArgumentCmd(tokens);
    }

    if (cmd_name == "echo" || cmd_name == "wc" ||
        cmd_name == "tr" || cmd_name == "head") {
        return parseOptionalArgumentCmd(tokens);
    }

    Exception::unknownCommand(cmd_name);
}

Command* Parser::parsePipeline(const vector<Token>& tokens){

    vector<vector<Token>> segments = extractPipelineSegments(tokens);

    PipelinePosition pos;
    for (int i = 0; i < segments.size(); i++) {
        if (i == 0) pos = PipelinePosition::START;
        else if (i == segments.size() - 1) pos = PipelinePosition::END;
        else pos = PipelinePosition::MIDDLE;

        validatePipelineSegment(segments[i], pos);
    }

    vector<Command*> commands;
    for (auto tokens : segments) {
        Command* cmd = parseTokens(tokens);
        commands.push_back(cmd);
    }

    return new Pipeline(commands);


    return nullptr;
    
}

vector<vector<Token>> Parser::extractPipelineSegments(const vector<Token>& tokens) {
    vector<vector<Token>> segments;
    vector<Token> current;

    for (auto t : tokens) {
        if (t.kind == TokenType::Pipe) {
            segments.push_back(current);
            current.clear();
        }
        else {
            current.push_back(t);
        }

    }
    segments.push_back(current);

    return segments;
}

void Parser::validatePipelineSegment(const vector<Token>& segment, PipelinePosition position){

    if (segment.empty()) Exception::emptyCommand();
    if (segment[0].kind != TokenType::Word) Exception::badTypeCommand();

    string cmd = segment[0].value;

    // Komanda bez ulaza mora biti na pocetku
    if ((cmd == "time" || cmd == "date") && position != PipelinePosition::START) Exception::commandAllowedOnStart(cmd);
    if (cmd == "touch" || cmd == "rm" || cmd == "truncate" || cmd == "prompt" || cmd == "batch") Exception::commandNotAllowedPipe(cmd);


    for (int i = 1; i < segment.size(); i++) {
        Token t = segment[i];

        if (position == PipelinePosition::START || position == PipelinePosition::MIDDLE) {
            if (t.kind == TokenType::RedirectOutput || t.kind == TokenType::DoubleRedirectOutput)
                Exception::commandNotAllowedOutPipe(cmd);
        }
        else if (position == PipelinePosition::END || position == PipelinePosition::MIDDLE) {
            if (t.kind == TokenType::RedirectInput)
                Exception::commandNotAllowedInPipe(cmd);

            if ((t.kind == TokenType::QuotedString || t.kind == TokenType::Word) && (i == 1 || i == 2))
            {
                Exception::commandNotAllowedInPipe(cmd);
            }
        }
    }
}




Command* Parser::parseNullArgumentCmd(const vector<Token>& tokens)
// moze imati samo izlaznu redirekciju
{
    string cmd_name = tokens[0].value;
    Stream* stream = Stream::createStream(tokens, 1, defaultOutput, "timedate");

    if (cmd_name == "time") {
        return new Time(stream);
    }
    if (cmd_name == "date") {
        return new Date(stream);
    }
}

Command* Parser::parseArgumentCmd(const vector<Token>& tokens){
    // ArgumentCmd komande NE ULAZE u Pipeline i nemaju niti ulaznu niti izlaznu redirekciju
    // jedini izuzetak je batch komanda koja moze imati izlaznu redirekciju

    string cmd_name = tokens[0].value;
    string argument = tokens[1].value;

    if (cmd_name != "batch" && tokens.size() > 2) Exception::tooManyArguments(cmd_name);

    if (cmd_name == "touch") {
        return new Touch(argument);
    }
    if (cmd_name == "prompt") {
        return new Prompt(argument);
    }
    if (cmd_name == "truncate") {
        return new Truncate(argument);
    }
    if (cmd_name == "rm") {
        return new Rm(argument);
    }
    if (cmd_name == "batch") {
        return makeBatch(tokens);
    }

    return nullptr;
}

Command* Parser::parseOptionalArgumentCmd(const vector<Token>& tokens)
{
    string cmd_name = tokens[0].value;

    if (cmd_name == "echo") {
        return makeEcho(tokens);
    }
    if (cmd_name == "wc") {
        return makeWc(tokens);
    }
    if (cmd_name == "tr") {
        return makeTr(tokens);
    }
    if (cmd_name == "head") {
        return makeHead(tokens);
    }

}

Command* Parser::makeEcho(const vector<Token>& tokens){
    int i = 1;

    Token argument = getArgument(tokens, i);

    Stream* stream = Stream::createStream(tokens, i, argument, defaultOutput, "echo");
    return new Echo(stream);
}


Command* Parser::makeWc(const vector<Token>& tokens){
    int i = 1;

    if (i >= tokens.size() || tokens[i].kind != TokenType::Option) Exception::optionExpected("wc", i + 1);
    Token option = tokens[i];
    i++;

    Token argument = getArgument(tokens, i);

    Stream* stream = Stream::createStream(tokens, i, argument, defaultOutput, "wc");

    // -w ili -c
    if (option.value == "w")
        return new WcWord(stream);
    if (option.value == "c")
        return new WcCharacter(stream);
   
    Exception::invalidOption("wc", "-w -c");
}

Command* Parser::makeTr(const vector<Token>& tokens){
    string what = "", with = "";
    int i = 1;

    Token argument = getArgument(tokens, i);

    if (i >= tokens.size() || tokens[i].kind != TokenType::Option) Exception::optionExpected("tr", i + 1);
    what = tokens[i].value;
    i++;

    if (i < tokens.size() && tokens[i].kind == TokenType::QuotedString) with = tokens[i].value;
    i++;

    Stream* stream = Stream::createStream(tokens, i, argument, defaultOutput, "tr");

    return new Tr(stream, what, with);
}

Command* Parser::makeHead(const vector<Token>& tokens){
    int i = 1;

    if (i >= tokens.size() || tokens[i].kind != TokenType::Option) Exception::optionExpected("head", i + 1);
    Token ncount = tokens[i];
    i++;
    int count;
    if (!validateCount(ncount.value, count)) Exception::invalidOption("head", "-nddddd, d=[0-9]");

    Token argument = getArgument(tokens, i);

    Stream* stream = Stream::createStream(tokens, i, argument, defaultOutput, "tr");

    return new Head(stream, count);
}

Command* Parser::makeBatch(const vector<Token>& tokens){

    if (tokens.size() > 4) Exception::tooManyArguments("batch");

    string argument = tokens[1].value;
    if (tokens.size() == 2) return new Batch(argument, this);

    if (tokens[2].kind != TokenType::RedirectOutput && tokens[2].kind != TokenType::DoubleRedirectOutput) Exception::onlyOutRedirectAllowed("batch");

    if (tokens.size() < 4 || tokens[3].kind != TokenType::Word) Exception::missingRedirectionArgument("batch", tokens[2]);

    return new Batch(argument, tokens[3].value, this);
}


//------------------------------------------------------------------------------------------------------------------------------------

vector<Token> Parser::tokenize(string line) {
    int i = 0;
    vector<Token> tokens;

    while (i < line.size()) {

        if (isspace(line[i])) {
            i++;
            continue;
        }
        else if (line[i] == '"')
        {
            tokens.push_back(
                Token(TokenType::QuotedString, readQuoted(line, i))
            );
        }
        else if(line[i] == '-') {  // treba popravka GRESKA
            if (i + 1 < line.size() && line[i + 1] == '"') {
                tokens.push_back(
                    Token(TokenType::Option, readQuoted(line, ++i))
                );
            }
            else {
                tokens.push_back(
                    Token(TokenType::Option, readWord(line, ++i))
                );
            }
        }
        else if (line[i] == '<') {
            tokens.push_back(
                Token(TokenType::RedirectInput)
            );
        }
        else if (line[i] == '>' && i + 1 < line.size() && line[i + 1] == '>') {
            i++;
            tokens.push_back(
                Token(TokenType::DoubleRedirectOutput)
            );
        }
        else if (line[i] == '>') {
            tokens.push_back(
                Token(TokenType::RedirectOutput)
            );
        }
        else if (line[i] == '|') {
            tokens.push_back(
                Token(TokenType::Pipe)
            );
        }
        else if (isalpha(line[i])){
            tokens.push_back(
                Token(TokenType::Word, readWord(line, i))
            );
        }
        else {
            Exception::unexpectedCharacter(line, i);
        }

        i++;
    }

    return tokens;
}

//obe pomocne funkcije ulaze sa i koji oznacava prvi detektovan karakter
string Parser::readQuoted(const string& line, int& i)
{
    if (i == line.size() - 1) Exception::missingCharacters(line, i);

    string quoted;
    i++;
    while (line[i] != '"') {

        quoted.push_back(line[i]);
        i++;

        if (i > line.size() - 1) Exception::missingClosedQuotation(line, i);
    }

    return quoted;
}

string Parser::readWord(const string& line, int& i)
{
    if( i == line.size()) Exception::missingCharacters(line, i);

    while (isspace(line[i])) {
        i++;
        if (i == line.size()) Exception::missingCharacters(line, i);
    }

    string word;
    while (!isspace(line[i])) {

        if (!isalnum(line[i]) && line[i] != '-' && line[i] != '_' && line[i] != '.') Exception::unexpectedCharacter(line, i);

        word.push_back(line[i]);

        if (i == line.size() - 1) break;

        i++;
    }
    return word;
}
