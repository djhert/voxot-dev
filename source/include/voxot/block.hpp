#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "blockregister.hpp"
#include "chunk.hpp"
#include "meshdata.hpp"
#include "metablock.hpp"
#include "shapekey.hpp"
#include "voxot.hpp"

using namespace godot;

namespace Voxot {

class Chunk;

class Block {
public:
	virtual const bool isVisible(const Direction &) { return false; };
	virtual const bool isSolid(const Direction &) { return false; };

	Block(){};
	~Block(){};
	virtual void Draw(Chunk *, MeshData *,
			const int &, const int &, const int &){};

protected:
	virtual void FaceUp(MeshData *,
			const int &, const int &, const int &){};
	virtual void FaceDown(MeshData *,
			const int &, const int &, const int &){};
	virtual void FaceNorth(MeshData *,
			const int &, const int &, const int &){};
	virtual void FaceSouth(MeshData *,
			const int &, const int &, const int &){};
	virtual void FaceWest(MeshData *,
			const int &, const int &, const int &){};
	virtual void FaceEast(MeshData *,
			const int &, const int &, const int &){};

	virtual UVTile FaceUV(const Direction &) { return { 0, 0 }; };
};
} // namespace Voxot

#endif