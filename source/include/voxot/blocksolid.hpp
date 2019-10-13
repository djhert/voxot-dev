#ifndef _BLOCKSOLID_H_
#define _BLOCKSOLID_H_

#include "block.hpp"

using namespace godot;

namespace Voxot {

class BlockSolid : public Block {
public:
	bool const isVisible(const Direction &) override;
	bool const isSolid(const Direction &) override;

	BlockSolid();
	~BlockSolid();

	void Draw(Chunk *, MeshData *,
			const int &, const int &, const int &) override;

	const static MetaBlock Block;

protected:
	void FaceUp(MeshData *, const int &, const int &, const int &) override;
	void FaceDown(MeshData *, const int &, const int &, const int &) override;
	void FaceNorth(MeshData *, const int &, const int &, const int &) override;
	void FaceSouth(MeshData *, const int &, const int &, const int &) override;
	void FaceWest(MeshData *, const int &, const int &, const int &) override;
	void FaceEast(MeshData *, const int &, const int &, const int &) override;
	UVTile FaceUV(const Direction &) override;

private:
	static bool registered;
};

namespace BlockRegister {
Registration<BlockSolid> _BlockSolid("solid");
}
} // namespace Voxot

#endif