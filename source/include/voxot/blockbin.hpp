#ifndef _BLOCKBIN_H_
#define _BLOCKBIN_H_

#include <string>
#include <unordered_map>

namespace Voxot {

class Block;

typedef Block *(*instanceGen)();

class BlockBin {
public:
	static BlockBin &instance();

	Block *Get(const std::string &typeName);
	void Init();
	bool Register(const std::string &typeName,
			const instanceGen &funcCreate);

private:
	BlockBin();
	BlockBin(const BlockBin &);
	~BlockBin();

	std::unordered_map<std::string, instanceGen> generators;
	std::unordered_map<std::string, Block *> objs;
};

} // namespace Voxot
#endif
