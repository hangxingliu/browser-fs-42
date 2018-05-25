// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)

#include <algorithm>
#include <sstream>
#include <vector>

#include "FSEntry.h"

using std::find_if;
using std::istringstream;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;
using std::weak_ptr;

FSEntry::FSEntry() {
  is_locked = false;
}

shared_ptr<FSEntry> FSEntry::make_de_dir(const string name, const shared_ptr<FSEntry> parent) {
	auto sp = make_shared<FSEntry>(FSEntry());
	if (parent == nullptr) {
		sp->parent = sp;
	} else {
		sp->parent = parent;
	}
	sp->type = dir;
	sp->self = sp;
	sp->name = name;
	sp->inode = nullptr;
	return sp;
}

shared_ptr<FSEntry> FSEntry::make_de_file(
	const string name,
	const shared_ptr<FSEntry> parent,
	const shared_ptr<FSInode> &inode) {

	auto sp = make_shared<FSEntry>(FSEntry());
	if (parent == nullptr) {
		sp->parent = sp;
	} else {
		sp->parent = parent;
	}
	sp->type = file;
	sp->self = sp;
	sp->name = name;
	sp->inode = inode;
	return sp;
}

	shared_ptr<FSEntry> FSEntry::find_child(const string name) const {
	// handle . and ..
	if (name == "..") {
		return parent.lock();
	} else if (name == ".") {
		return self.lock();
	}

	// search through contents and return ptr if found, otherwise nullptr
	auto named = [&] (const shared_ptr<FSEntry> de) {return de->name == name;};
	auto it = find_if(begin(contents), end(contents), named);
	if (it == end(contents)) {
		return nullptr;
	}

	return *it;
}

shared_ptr<FSEntry> FSEntry::add_dir(const string name) {
	auto new_dir = make_de_dir(name, self.lock());
	contents.push_back(new_dir);
	return new_dir;
}

shared_ptr<FSEntry> FSEntry::add_file(const string name) {
	auto new_file = make_de_file(name, self.lock(), make_shared<FSInode>());
	contents.push_back(new_file);
	return new_file;
}
