#include <stdio.h>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

#include <string>
#include <sstream>
#include <vector>

#include "../core/StorageDevices/InMemory128MBDevice.h"
#include "../core/FSMain.h"

#define sync_io fflush(stdout); fflush(stderr);

static char unsafeBuffer[1024];
static FSMain* fsMain = nullptr;
static InMemory128MBDevice* device = nullptr;

const std::string REPL_PROMPT = "sh> ";
const uint BLOCK_SIZE = 1024;
const uint DIRECT_BLOCKS = 100;
static uint LAST_CAPACITY = 0;

int init(int capacity) {
	LAST_CAPACITY = (uint) capacity;

	if(!device)
		device = new InMemory128MBDevice((uint) capacity);
	if(!fsMain)
		fsMain = new FSMain(device, BLOCK_SIZE, DIRECT_BLOCKS);
	printf("filesystem initialized!\n");
	sync_io;
//	std::cout << "filesystem initialized!" << std::endl;
	return 0;
}

std::string getCurrentPath() {
	if(fsMain) return fsMain->getPwd();
	return "";
}

void replShowPrompt() {
	printf("%s", REPL_PROMPT.c_str());
	sync_io;
}
int repl(std::string commands) {
	std::vector<std::string> args;
	args.clear();

	std::istringstream iss(commands);
	std::string part;
	std::string name;
	uint index = 0;
	while (iss >> part) {
		if(index == 0) name = part;
		args.push_back(part);
		index++;
	}

	bool executeOnce = true;
	while(executeOnce) {
		executeOnce = false;

		if(index == 0)
			break;

		if(!fsMain)
			break;

		if (name == "df") {
			printf("Capacity of storage device: %d\n", device->getDeviceCapacity());
			fsMain->dumpFreeDataBlocks(args);
			break;
		}

		if(name == "debug") {
			if(args.size() < 2) {
				printf("Current debug log status: %s\n", (FSMain::debugLog ? "on" : "off") );
			} else if(args[1] == "on" || args[1] == "off") {
				FSMain::debugLog = args[1] == "on";
				printf("Switch debug log status to %s\n", (FSMain::debugLog ? "on" : "off") );
			} else {
				fprintf(stderr, "Usage: %s on|off \n", name.c_str());
			}
			break;
		}

		if (name == "mkfs" || name == "format") {
			if (args.size() != 1) {
				fprintf(stderr, "%s: too many operands\n", name.c_str());
				break;
			}
			delete(fsMain);
			delete(device);
			device = new InMemory128MBDevice(LAST_CAPACITY);
			fsMain = new FSMain(device, BLOCK_SIZE, DIRECT_BLOCKS);
			break;
		}

		if(name == "open") { fsMain->open(args); break; }
		if(name == "read") { fsMain->read(args); break; }
		if(name == "write") {
			if(args.size() >= 3) {
				auto start = commands.find("\"");
				auto end = commands.find("\"", start+1);
				if (start != std::string::npos && end != std::string::npos) {
					std::string w_str = commands.substr(start+1, end-start-1);
					auto rn = commands.find_first_not_of(" \t",end+1);
					if (rn != std::string::npos) {
						args = {args[0], args[1], w_str, commands.substr(rn)};
					} else {
						args = {args[0], args[1], w_str};
					}
				}
			} else {
				args = {"write"};
			}
			fsMain->write(args);
			break;
		}
		if (args[0] == "seek") { fsMain->seek(args); break; }
		if (args[0] == "close") { fsMain->close(args); break; }

		if (args[0] == "mkdir") { fsMain->mkdir(args); break; }
		if (args[0] == "rmdir") { fsMain->rmdir(args); break; }

		if (args[0] == "rm") { fsMain->unlink(args); break; }
		if (args[0] == "unlink") { fsMain->unlink(args); break; }

		if (args[0] == "cp") { fsMain->cp(args); break; }
		if (args[0] == "link") { fsMain->link(args); break; }

		if (args[0] == "ls") { fsMain->ls(args); break; }
		if (args[0] == "stat") { fsMain->stat(args); break; }
		if (args[0] == "tree") { fsMain->tree(args); break; }

		if (args[0] == "cat") { fsMain->cat(args); break; }
		if (args[0] == "touch") { fsMain->touch(args); break; }
		if (args[0] == "a") { fsMain->fillA(args); break; }
		if (args[0] == "txt") { fsMain->createText(args); break; }

		if (args[0] == "cd") { fsMain->cd(args); break; }
		if (args[0] == "pwd") { fsMain->printwd(args); break; }

		printf("error: unknown command \"%s\"\n", name.c_str());
	}


	// replShowPrompt();
	sync_io;
	return 0;
}

emscripten::val getStorageDeviceData(int offset, int length) {
	char* buffer = unsafeBuffer;
	if(device)
		buffer = device->lowLevelAsscess() + offset;
	return emscripten::val(emscripten::typed_memory_view((uint) length, buffer));
}

EMSCRIPTEN_BINDINGS(browser_fs_42) {
	emscripten::function("fs_init", &init);
	emscripten::function("fs_repl", &repl);
	emscripten::function("fs_pwd", &getCurrentPath);
	emscripten::function("fs_repl_prompt", &replShowPrompt);
	emscripten::function("fs_access_device", &getStorageDeviceData);
}
