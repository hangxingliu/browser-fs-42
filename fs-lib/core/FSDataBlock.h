// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#ifndef CORE_FS_DATA_BLOCK_H
#define CORE_FS_DATA_BLOCK_H

#include <string.h>
#include <string>
#include <list>
#include "Base/Types.h"

class FSDataBlock {
public:
	uint num_blocks;
	uint pos;
	FSDataBlock(uint num_blocks, uint pos): num_blocks(num_blocks), pos(pos) {}
	std::string toString() {
		char buf[128];
		sprintf(buf, "FSDataBlock { num_blocks: %u, pos: %u }", num_blocks, pos);
		return std::string(buf);
	}
};

#endif
