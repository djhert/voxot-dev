#ifndef _BLOCKAIR_H_
#define _BLOCKAIR_H_

#include "block.hpp"

namespace Voxot {
class BlockAir : public Block {
public:
	BlockAir(){};
	~BlockAir(){};

	const static MetaBlock Block;
};

namespace BlockRegister {
Registration<BlockAir> _BlockAir("air");
}
} // namespace Voxot

#endif