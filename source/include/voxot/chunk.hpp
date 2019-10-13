#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "block.hpp"
#include "blockbin.hpp"
#include "meshdata.hpp"
#include "metablock.hpp"
#include "voxot.hpp"
#include "world.hpp"

using namespace godot;

namespace Voxot {

class Block;
class World;
class MeshData;

class Chunk : public MeshInstance {
	GODOT_CLASS(Chunk, MeshInstance);

public:
	// Constructor
	Chunk(){};
	// Destroyer
	~Chunk();

	// Name of chunk
	String _name;

	// Godot requirements
	static void _register_methods();
	void _init();
	void _ready();
	void _process(double);

	// Chunk functions
	virtual void Init(){};
	virtual void Ready(){};
	virtual void Update(const double &){};
	virtual void Generate();

	static void Render(Chunk *);
	static String toName(const int &, const int &, const int &);

	void setup(World *, const int &, const int &, const int &);
	Block *GetBlock(const int &, const int &, const int &);
	bool DeleteBlock(const int &, const int &, const int &);
	void dirty() { isDirty = true; };

	template <typename T>
	static T *New(World *w, const int &x, const int &y, const int &z) {
		T *newChunk = T::_new();
		newChunk->setup(w, x, y, z);
		return newChunk;
	}

	int X;
	int Y;
	int Z;

	int Width;
	int Height;
	int Depth;

	static MetaBlock AirBlock;

protected:
	MetaBlock ***Blocks;

	bool isDirty;
	std::atomic<bool> isUpdating;

	bool inBounds(const int &, const int &, const int &);

	World *_world;
	StaticBody *staticBody;
	CollisionShape *collisionShape;

	MeshData *meshData;
	Array meshArray;
	ConcavePolygonShape *collisionMesh;
};
} // namespace Voxot
#endif