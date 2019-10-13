#include "blockbin.hpp"

namespace Voxot {
BlockBin::BlockBin() {
}

BlockBin::~BlockBin() {
}

Block *BlockBin::Get(const std::string &typeName) {
	auto it = objs.find(typeName);
	if (it != objs.end()) {
		return it->second;
	}

	return nullptr;
}

bool BlockBin::Register(const std::string &typeName, const instanceGen &funcCreate) {
	return generators.insert(std::make_pair(typeName, funcCreate)).second;
}

void BlockBin::Init() {
	for (auto const &x : generators) {
		objs.insert(std::make_pair(x.first, x.second()));
	}
	generators.clear();
}

BlockBin &BlockBin::instance() {
	static BlockBin instance;
	return instance;
}
} // namespace Voxot