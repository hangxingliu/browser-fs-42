// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

#include "FSInode.h"

using std::list;
using std::shared_ptr;
using std::sort;
using std::vector;
using std::cout;
using std::endl;

uint FSInode::block_size = 0;
list<FSDataBlock> * FSInode::free_list = nullptr;

FSInode::FSInode(): size(0), blocks_used(0), i_blocks(new vector<vector<uint>>()) {
}

FSInode::~FSInode() {
	if (blocks_used == 0) {
		return;
	} else if (blocks_used == 1) {
		free_list->emplace_front(1, d_blocks[0]);
		return;
	}

	vector<uint> blocks;

	for (uint block : d_blocks)
		blocks.push_back(block);

	for (auto vec: *i_blocks) {
		for (uint block: vec) {
			blocks.push_back(block);
		}
	}

	sort(begin(blocks), end(blocks));
	cout << "DEBUG: ~FSInode blocks: " << blocks.size() << endl;
	for(auto& b: blocks)
		cout << "DEBUG:   offset:" << b << endl;

	uint start = blocks.front();
	uint last = start;
	uint size = block_size;
	blocks.erase(begin(blocks));
	for (uint block : blocks) {
		if (block - last != block_size) {
			free_list->emplace_back(size / block_size, start);
			last = start = block;
			size = 0;
		} else {
			last = block;
			size += block_size;
		}
	}

	free_list->emplace_front(size / block_size, start);
}

