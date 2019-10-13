#include "voxot.hpp"
#include "chunk.hpp"
#include "world.hpp"

namespace Voxot {
void RegisterVoxot() {
	godot::register_class<World>();
	godot::register_class<Chunk>();
}

template <typename T>
bool Util::Register() {
	godot::register_class<T>();
	return true;
}

template <typename T>
void Util::RegisterWorld() {
	godot::register_property<T, int>("Chunk/Width", &T::setChunkWidth, &T::getChunkWidth, 12);
	godot::register_property<T, int>("Chunk/Height", &T::setChunkHeight, &T::getChunkHeight, 12);
	godot::register_property<T, int>("Chunk/Depth", &T::setChunkDepth, &T::getChunkDepth, 12);

	godot::register_property<T, godot::Dictionary>("Material/Materials", &T::MaterialList, godot::Dictionary::make<godot::String, godot::Variant>("default", GODOT_VARIANT_TYPE_NIL));
	godot::register_property<T, int>("Material/Tiles", &T::settilesize, &T::gettilesize, 2);

	godot::register_method("_ready", &T::_ready);
	godot::register_method("_process", &T::_process);
}
} // namespace Voxot