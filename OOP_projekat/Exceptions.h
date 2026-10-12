#pragma once
#include<string>

struct Token;

using namespace std;


class Exception {
public:

	string getMessage();

	static void fileAlreadyExists(const string& name, const string& filename);
	static void fileNotExists(const string& name, const string& filename);
	static void cannotCreateFile(const string& name, const string& filename);
	static void unableToOpenFile(const string& name, const string& filename);
	static void unableToDeleteFile(const string& name, const string& filename);


	//sintaksne greske
	static string syntaxErorrMessage(const string& line, int position);
	static void unexpectedCharacter(const string& line, int position);
	static void missingCharacters(const string& line, int position);
	static void missingClosedQuotation(const string& line, int position);

	static void unknownCommand(const string& name);
	static void badTypeCommand();
	static void emptyCommand();
	static void tooManyArguments(const string& name);
	static void missingRedirectionArgument(const string& name, Token t);
	static void onlyOutRedirectAllowed(const string& name);
	static void optionExpected(const string& name, int i);
	static void invalidOption(const string& name, const string& expected);

	//semanticke greske prilikom kreiranja streama
	static void multipleInputSources(const string& name);
	static void multipleOutputSources(const string& name);
	static void unexpectedArgument(const string& name, Token t);

	//Pipeline greske
	static void commandAllowedOnStart(const string& name);
	static void commandNotAllowedPipe(const string& name);
	static void commandNotAllowedOutPipe(const string& name);
	static void commandNotAllowedInPipe(const string& name);



private:
	Exception(string message);

	string message;
};

inline string Exception::getMessage() { return message; }