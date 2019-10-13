#ifndef _MESHDATA_H_
#define _MESHDATA_H_

#include "voxot.hpp"

using namespace godot;

namespace Voxot {

class MeshData {
public:
	PoolVector3Array verts;
	PoolVector3Array normals;
	PoolVector2Array uvs;
	PoolRealArray tangents;

	MeshData();
	~MeshData();

	void Square(const Vector3 &, const Vector3 &, const Vector3 &, const Vector3 &);
	void UVSquare(const Vector3 &, const Vector3 &, const Vector3 &, const Vector3 &, const Vector2 &, const Vector2 &, const Vector2 &, const Vector2 &);

	void clear();

private:
	void calcNormal(const Vector3 &, const Vector3 &, const Vector3 &);
	void calcTangent(const Vector3 &, const Vector3 &, const Vector3 &, const Vector2 &, const Vector2 &, const Vector2 &);
};
} // namespace Voxot

#endif
