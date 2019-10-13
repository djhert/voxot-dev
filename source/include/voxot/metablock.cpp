#include "metablock.hpp"

namespace Voxot {
MetaBlock::MetaBlock() {
	name = "air";
	type = 0;
}

MetaBlock::MetaBlock(std::string n) {
	name = n;
	type = 0;
}

MetaBlock::MetaBlock(std::string n, int t) {
	name = n;
	type = t;
}

bool MetaBlock::operator==(const MetaBlock &a) const {
	if (name == a.name)
		if (type == a.type)
			return true;
	return false;
}

bool MetaBlock::operator!=(const MetaBlock &a) const {
	if (name == a.name)
		if (type == a.type)
			return false;
	return true;
}
} // namespace Voxot