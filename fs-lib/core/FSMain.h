// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#ifndef CORE_FS_MAIN_H
#define CORE_FS_MAIN_H

#include <list>
#include <map>
#include <string>
#include <vector>

#include "StorageDevices/DeviceInterface.h"
#include "FSDataBlock.h"
#include "FSInode.h"
#include "FSEntry.h"

class FSMain {

	enum Mode {R, W, RW};
	struct Descriptor {
		Mode mode;
		uint byte_pos;
		std::weak_ptr<FSInode> inode;
		std::weak_ptr<FSEntry> from;
		uint fd;
	};

	bool getMode(Mode *mode, std::string mode_s);

	struct PathRet {
		bool invalid_path = false;
		std::string final_name;
		std::shared_ptr<FSEntry> parent_node;
		std::shared_ptr<FSEntry> final_node;
	};

	DeviceInterface* storageDevice = nullptr;

	// std::fstream disk_file;
	uint block_size;
	uint direct_blocks;
	uint num_blocks = 0;

	// FSEntry root;
	std::list<FSDataBlock>free_list;
	std::shared_ptr<FSEntry> root_dir;
	std::shared_ptr<FSEntry> pwd;
	std::map<uint, Descriptor> open_files;
	uint next_descriptor = 0;

	void init_disk();
	std::unique_ptr<PathRet> parse_path(std::string path_str) const;
	bool basic_open(Descriptor *d, std::vector <std::string> args);
	std::unique_ptr<std::string> basic_read(Descriptor &desc, const uint size);
	uint basic_write(Descriptor &desc, const std::string data);
	bool basic_close(uint fd);

public:
	FSMain(DeviceInterface* storageDevice,
		const uint block_size,
		const uint direct_blocks);
	~FSMain();

	static bool debugLog;

	void open(std::vector<std::string> args);
	void read(std::vector<std::string> args);
	void write(std::vector<std::string> args);
	void seek(std::vector<std::string> args);
	void close(std::vector<std::string> args);

	void mkdir(std::vector<std::string> args);
	void rmdir(std::vector<std::string> args);

	void cd(std::vector<std::string> args);
	void printwd(std::vector<std::string> args);

	void link(std::vector<std::string> args);
	void unlink(std::vector<std::string> args);

	void stat(std::vector<std::string> args);
	void ls(std::vector<std::string> args);
	void tree(std::vector<std::string> args);

	void touch(std::vector<std::string> args);
	void createText(std::vector<std::string> args);
	void fillA(std::vector<std::string> args);
	void cat(std::vector<std::string> args);

	void cp(std::vector<std::string> args);

	std::string getPwd();

	void dumpFreeDataBlocks(std::vector<std::string> args);
};

#endif
