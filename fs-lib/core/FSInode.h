// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#ifndef CORE_FS_INODE_H
#define CORE_FS_INODE_H

#include <sys/types.h>
#include <list>
#include <memory>
#include <vector>
#include <string>
#include "FSDataBlock.h"


class FSInode {
public:
	static uint block_size;
	static std::list<FSDataBlock> *free_list;
	uint size;
	uint blocks_used;
	std::vector<uint> d_blocks;
	std::unique_ptr<std::vector<std::vector<uint>>> i_blocks;

	FSInode();
	~FSInode();
};

#endif
