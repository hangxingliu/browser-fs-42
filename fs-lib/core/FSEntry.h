// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#ifndef CORE_FS_ENTRY_H
#define CORE_FS_ENTRY_H

#include <list>
#include <memory>
#include <string>
#include "Base/Types.h"
#include "FSDataBlock.h"
#include "FSInode.h"

enum FSEntryType { file, dir };

class FSEntry: public std::enable_shared_from_this<FSEntry> {
	FSEntry();
public:
	static std::shared_ptr<FSEntry> make_de_dir(
		const std::string name,
		const std::shared_ptr<FSEntry> parent);
	static std::shared_ptr<FSEntry> make_de_file(
		const std::string name,
		const std::shared_ptr<FSEntry> parent,
		const std::shared_ptr<FSInode> &inode=nullptr);

	uint block_size;
	FSEntryType type;
	std::string name;
	std::weak_ptr<FSEntry> parent;
	std::weak_ptr<FSEntry> self;
	std::shared_ptr<FSInode> inode;
	std::list<std::shared_ptr<FSEntry>> contents;
	bool is_locked;

	std::shared_ptr<FSEntry> find_child(const std::string name) const;
	std::shared_ptr<FSEntry> add_dir(const std::string name);
	std::shared_ptr<FSEntry> add_file(const std::string name);
};

#endif /* FS_ENTRY_H */
