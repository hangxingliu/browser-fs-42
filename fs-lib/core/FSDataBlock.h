// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#ifndef CORE_FS_DATA_BLOCK_H
#define CORE_FS_DATA_BLOCK_H

#include <list>
#include "Base/Types.h"

class FSDataBlock {
public:
	uint num_blocks;
	uint pos;
	FSDataBlock(uint num_blocks, uint pos): num_blocks(num_blocks), pos(pos) {}
};

#endif
