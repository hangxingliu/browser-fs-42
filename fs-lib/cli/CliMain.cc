// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../core/FSMain.h"
#include "../core/StorageDevices/InMemory128MBDevice.h"

using namespace std;

const string PROMPT = "sh> ";
const uint BLOCKSIZE = 1024;
const uint DIRECTBLOCKS = 100;

void repl() {
	InMemory128MBDevice device;
	FSMain *fs = new FSMain(&device, BLOCKSIZE, DIRECTBLOCKS);

	string cmd;
	vector<string> args;
	string token;

	cout << PROMPT;
	while (getline(cin, cmd)) {
		args.clear();
		istringstream iss(cmd);
		while (iss >> token) {
			args.push_back(token);
		}

		if (args.size() == 0) {
			cout << PROMPT;
			continue;
		}

		if (args[0] == "debug") {
			uint offset = 0;
			try {
				offset = (uint) stoi(args.size() > 1 ? args[1] : "0");
			} catch (...) {
				cerr << "device-dump: offset \"" << args[1] << "\" is invalid!" << endl;
				continue;
			}
			if(offset >= device.getDeviceCapacity()) {
				cerr << "device-dump: offset \"" << args[1] << "\" is invalid (greater than device capacity)" << endl;
				continue;
			}
			char buffer[16];
			uint len = device.read(offset, 16, buffer);
			cout << offset << ": ";
			for(uint i = 0 ; i < len ; i ++ )
				cout << ((int) buffer[i]) << " ";
			cout << endl;

			fs->dumpFreeDataBlocks(args);

			cout << PROMPT;
			continue;
		}

		if (args[0] == "mkfs") {
			if (args.size() == 1) {
				delete(fs);
				fs = new FSMain(&device, BLOCKSIZE, DIRECTBLOCKS);
			} else {
				cerr << "mkfs: too many operands" << endl;
			}
		} else if (args[0] == "open") {
			fs->open(args);
		} else if (args[0] == "read") {
			fs->read(args);
		} else if (args[0] == "write") {
			if(args.size() >= 3) {
				auto start = cmd.find("\"");
				auto end = cmd.find("\"", start+1);
				cout << start << "  " << end << endl;
				if (start != string::npos && end != string::npos) {
					string w_str = cmd.substr(start+1, end-start-1);
					auto rn = cmd.find_first_not_of(" \t",end+1);
					if (rn != string::npos) {
						args = {args[0], args[1], w_str, cmd.substr(rn)};
					} else {
						args = {args[0], args[1], w_str};
					}
				}
			} else {
				args = {"write"};
			}
			fs->write(args);
		} else if (args[0] == "seek") {
			fs->seek(args);
		} else if (args[0] == "close") {
			fs->close(args);
		} else if (args[0] == "touch") {
			fs->touch(args);
		} else if (args[0] == "create-text") {
			fs->createText(args);
		} else if (args[0] == "mkdir") {
			fs->mkdir(args);
		} else if (args[0] == "rmdir") {
			fs->rmdir(args);
		} else if (args[0] == "cd") {
			fs->cd(args);
		} else if (args[0] == "link") {
			fs->link(args);
		} else if (args[0] == "unlink") {
			fs->unlink(args);
		} else if (args[0] == "stat") {
			fs->stat(args);
		} else if (args[0] == "ls") {
			fs->ls(args);
		} else if (args[0] == "cat") {
			fs->cat(args);
		} else if (args[0] == "cp") {
			fs->cp(args);
		} else if (args[0] == "tree") {
			fs->tree(args);
		} else if (args[0] == "import") {
			// fs->import(args);
		} else if (args[0] == "export") {
			// fs->FS_export(args);
		} else if (args[0] == "exit") {
			break;
		} else if (args[0] == "pwd") {
			fs->printwd(args);
		} else {
			cout << "unknown command: " << args[0] << endl;
		}
		cout << PROMPT;
	}

	delete(fs);
	return;
}

int main() {
	repl();
    return 0;
}
