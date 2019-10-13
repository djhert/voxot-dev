#ifndef _VSHAPEKEY_H_
#define _VSHAPEKEY_H_

#include "voxot.hpp"

using namespace godot;

namespace Voxot {
class ShapeKey {
public:
	static ShapeKey &Get();
	Vector3 At(const int &, const int &, const int &,
			const int &, const float &);

private:
	ShapeKey();
	~ShapeKey();

	const static Vector2 key[25];
};
} // namespace Voxot

#endif