#include "myworld.hpp"

bool myworld::registered = [] {
	bool registered = Voxot::Util::Register<myworld>();
};

void myworld::Generate() {
#ifdef _DEBUG
	godot::Godot::print("Generating World New");
#endif
}

void myworld::_register_methods() {
	//Voxot::World::Register<myworld>();
	godot::Godot::print("myworld");
}