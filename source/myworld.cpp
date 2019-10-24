#include "myworld.hpp"

REGISTER_CLASS(myworld)

myworld::myworld() {}
myworld::~myworld() {}

void myworld::Generate() {
	Voxot::Chunk *ch = _NewChunk("default");
	ch->setup(this, 0, 0, 0);
	this->add_child(ch);

	ch = _NewChunk("default");
	ch->setup(this, ChunkWidth, 0, 0);
	this->add_child(ch);

	ch = _NewChunk("default");
	ch->setup(this, 0, 0, ChunkDepth);
	this->add_child(ch);

	ch = _NewChunk("default");
	ch->setup(this, ChunkWidth, 0, ChunkDepth);
	this->add_child(ch);
}

void myworld::_register_methods() {
	GDNATIVE_REGISTER(myworld)
	Voxot::World::Register<myworld>();
}