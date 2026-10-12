#include "Parser.h"
#include "NullArgumentCmd.h"
#include "Touch.h"
#include "Echo.h"
#include "Wc.h"



Stream* Parser::createStream(Token argument, string name){

    return argumentStream(argument, name);
}

Stream* Parser::createStream(){
    return withoutArgumentStream();
}

Stream* Parser::argumentStream(const Token& argument, string name) {// za sada radi samo input bez outputa(redirection)
    //
    if (argument.kind == TokenType::Word) // fajl
    {
        ifstream* fileInput = new ifstream(argument.value);
        if (!*fileInput) Exception::unableToOpenFile(name, argument.value);
        return new Stream(fileInput, &cout);
    }

    stringstream* ss = new stringstream;

    if (argument.kind == TokenType::QuotedString)
    {
        *ss << argument.value;
        cin.clear(); //ocisti buffer zbog EOF
        return new Stream(ss, &cout);
    }
}

Stream* Parser::withoutArgumentStream() {
    stringstream* ss = new stringstream;

    string str;
    while (getline(cin, str)) {
        *ss << str << '\n';
    }
    cin.clear(); //ocisti buffer 

    return new Stream(ss, &cout);
}

Command* Parser::parseCommand(string line)
{
    vector<Token> tokens = tokenize(line);

    if (tokens.empty())
        return nullptr;

    Token cmd = tokens[0];
    if (cmd.kind != TokenType::Word) {}// GRESKA
    string cmd_name = cmd.value;

    if (cmd_name == "time" || cmd_name == "date") {
        return parseNullArgumentCmd(tokens);
    }

    if (cmd_name == "touch") {
        return parseArgumentCmd(tokens);
    }

    if (cmd_name == "echo" || cmd_name == "wc") {
        return parseOptionalArgumentCmd(tokens);
    }
}

vector<Token> Parser::tokenize(string line){
    int i = 0;
    vector<Token> tokens;

    while (i < line.size()) {

        if (isspace(line[i])) { // Treba izmeniti

        }
        else if (line[i] == '"')
        {
            tokens.push_back(
                Token(TokenType::QuotedString, readQuoted(line, i))
            );
        }
        else {
            tokens.push_back(
                Token(TokenType::Word, readWord(line, i))
            );
        }

        i++;
    }

    return tokens;
}


Command* Parser::parseNullArgumentCmd(const vector<Token>& tokens)
//trenutno nije podrzana redirekcija ili pipe, pa su uslovi jednostavni
{
    if(tokens.size() != 1) { } // GRESKA

    string cmd_name = tokens[0].value;

    if (cmd_name == "time") {
        return new Time();
    }
    if (cmd_name == "date") {
        return new Date();
    }
}

Command* Parser::parseArgumentCmd(const vector<Token>& tokens){
    // da li je dobar uslov za gresku?
    if(tokens.size() != 2) { } // GRESKA

    string cmd_name = tokens[0].value;
    string argument = tokens[1].value;

    if (cmd_name == "touch") {
        return new Touch(argument);
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
}

Command* Parser::makeEcho(const vector<Token>& tokens)
// trenutan format echo
//                 echo "argument echa"
//                 echo filename
{
    if (tokens.size() == 2) {
        Token argument = tokens[1];
        return new Echo(createStream(argument, "echo"));
    }
    if (tokens.size() == 1) {
        return new Echo(createStream());
    }
}

Command* Parser::makeWc(const vector<Token>& tokens){
    string argument = "";

    if(tokens.size() < 2) { } // GRESKA

    Stream* stream = nullptr;
    if (tokens.size() == 3) {
        stream = createStream(tokens[2], "wc");
    }
    if (tokens.size() == 2) {
        stream = createStream();
    }

    string option = tokens[1].value;
    if(option[0] != OPTION_CHARACTER) { } // GRESKA

    // -w ili -c
    if (option[1] == 'w')
        return new WcWord(stream);
    if (option[1] == 'c')
        return new WcCharacter(stream);
   

    return nullptr;
}

//obe pomocne funkcije ulaze sa i koji oznacava prvi detektovan karakter
string Parser::readQuoted(const string& line, int& i)
{
    if (i == line.size() - 1) {} // GRESKA

    string quoted;
    i++;
    while (line[i] != '"') {
        quoted.push_back(line[i]);
        i++;

        if (i > line.size() - 1) {} //GRESKA
    }

    return quoted;
}

string Parser::readWord(const string& line, int& i)
{
    string word;
    while (!isspace(line[i])) {
        word.push_back(line[i]);

        if (i == line.size() - 1) break;

        i++;
    }
    return word;
}
