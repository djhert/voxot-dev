#include "myworld.hpp"

REGISTER_CLASS(myworld)

myworld::myworld() {}
myworld::~myworld() {}

void myworld::Generate() {
	this->add_child(Voxot::Chunk::New<Voxot::Chunk>(this, 0, 0, 0));
	this->add_child(Voxot::Chunk::New<Voxot::Chunk>(this, ChunkWidth, 0, 0));
	this->add_child(Voxot::Chunk::New<Voxot::Chunk>(this, 0, 0, ChunkDepth));
	this->add_child(Voxot::Chunk::New<Voxot::Chunk>(this, ChunkWidth, 0, ChunkDepth));
}

void myworld::_register_methods() {
	GDNATIVE_REGISTER(myworld)
	Voxot::World::Register<myworld>();
}