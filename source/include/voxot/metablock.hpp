#ifndef _METABLOCK_H_
#define _METABLOCK_H_

#include <string>

namespace Voxot {
struct MetaBlock {
	std::string name;
	int type;

	MetaBlock();
	MetaBlock(std::string);
	MetaBlock(std::string, int);

	bool operator==(const MetaBlock &) const;
	bool operator!=(const MetaBlock &) const;
};
} // namespace Voxot
#endif