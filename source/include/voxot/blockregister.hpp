#include "blockbin.hpp"
#include <Godot.hpp>

namespace Voxot {
namespace BlockRegister {
template <typename T>
class Registration {
public:
	Registration(const char *id) {
		BlockBin::instance().Register(id,
				[]() { return static_cast<Block *>(new T()); });
	}
};

} // namespace BlockRegister
} // namespace Voxot