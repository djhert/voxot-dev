#ifndef _WORLD_H_
#define _WORLD_H_

#include "block.hpp"
#include "blockbin.hpp"
#include "chunk.hpp"
#include "voxot.hpp"

using namespace godot;

namespace Voxot {

class Chunk;
//class Block;

class World : public Spatial {
	GODOT_CLASS(World, Spatial);

public:
	String _name;

	World();
	~World();

	static void _register_methods();
	template <class T>
	static void Register();

	void _init();
	void _ready();
	void _process(double);

	virtual void Init(){};
	virtual void Ready(){};
	virtual void Generate();
	virtual void Update(const double &){};

	void setChunkWidth(int);
	int getChunkWidth();

	void setChunkHeight(int);
	int getChunkHeight();

	void setChunkDepth(int);
	int getChunkDepth();

	void settilesize(int);
	int gettilesize();

	Ref<SpatialMaterial> GetMaterial(String);

	static float tileSize;

	Chunk *GetChunk(const String &);

	bool AddBlock(const Vector3 &, MetaBlock);
	bool DeleteBlock(const Vector3 &);
	MetaBlock *GetBock(const Vector3 &);

protected:
	int ChunkWidth;
	int ChunkHeight;
	int ChunkDepth;

	int WorldWidth;
	int WorldHeight;

	int tiles;

	Dictionary MaterialList;

	void LoadMaterials();
};
} // namespace Voxot

#endif