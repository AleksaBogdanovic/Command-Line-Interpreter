#pragma once
#include<string>

using namespace std;


class Exception {
public:

	string getMessage();

	static void fileAlreadyExists(const string& name, const string& filename);
	static void cannotCreateFile(const string& name, const string& filename);
	static void unableToOpenFile(const string& name, const string& filename);
private:
	Exception(string message);

	string message;
};

inline string Exception::getMessage() { return message; }