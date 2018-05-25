#include <iostream>
#include <string>

#include "Tests.h"

using namespace std;

#define check if( code != 0 ) { failed(); } else { success(); }

static string CYAN = "\x1b[36;1m";
static string GREEN = "\x1b[32m";
static string RED = "\x1b[31;1m";
static string RESET = "\x1b[0m";

static bool hasFailed = false;
static string currentTest = "";

void start(const string& name) {
	currentTest = move(name);
	cout << CYAN << "[.] Start test: " << currentTest << "..." << RESET << endl;
}

void failed() {
	hasFailed = true;
	cout << RED << "[-] failed!" << RESET << endl;
}

void success() {
	cout << GREEN << "[~] success!" << RESET << endl;
}

int main(int argc, char** argv) {
	for(int i = 1 ; i < argc ; i ++ ) {
		string arg(argv[i]);
		if(arg == "--no-color" || arg == "--color=off" || arg == "--color=no") {
			CYAN = ""; GREEN = ""; RED = ""; RESET = "";
			break;
		}
	}
	int code = 0;
	cout << CYAN << "[.] Start testing ..." << RESET << endl;

	// =========================================================

	start("InMemory128MBDevice");
	code = testInMemory128MBDevice(); check;

	// =========================================================


	if(hasFailed)
		cout << RED << "[-] some tests failed!" << RESET << endl;
	else
		cout << GREEN << "[+] all passed!" << RESET << endl;
	return hasFailed ? 1 : 0;
}
