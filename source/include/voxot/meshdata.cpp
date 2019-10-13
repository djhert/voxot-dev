#include "meshdata.hpp"

namespace Voxot {
MeshData::MeshData() {
	verts = PoolVector3Array();
	normals = PoolVector3Array();
	uvs = PoolVector2Array();
	tangents = PoolRealArray();
}

MeshData::~MeshData() {
}

void MeshData::UVSquare(const Vector3 &vbl, const Vector3 &vbr, const Vector3 &vtl, const Vector3 &vtr, const Vector2 &ubl, const Vector2 &ubr, const Vector2 &utl, const Vector2 &utr) {
	verts.push_back(vbl);
	verts.push_back(vbr);
	verts.push_back(vtl);
	calcNormal(vbl, vbr, vtl);
	uvs.push_back(utl);
	uvs.push_back(ubl);
	uvs.push_back(utr);
	calcTangent(vbl, vbr, vtl, utl, ubl, utr);

	verts.push_back(vbr);
	verts.push_back(vtr);
	verts.push_back(vtl);
	calcNormal(vbr, vtr, vtl);
	uvs.push_back(ubl);
	uvs.push_back(ubr);
	uvs.push_back(utr);
	calcTangent(vbr, vtr, vtl, ubl, ubr, utr);
}

void MeshData::calcNormal(const Vector3 &a, const Vector3 &b, const Vector3 &c) {
	Vector3 x, y, n;
	x = b - a;
	y = c - a;
	n = y.cross(x);
	n.normalize();
	normals.push_back(n);
	normals.push_back(n);
	normals.push_back(n);
}

void MeshData::calcTangent(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Vector2 &uva, const Vector2 &uvb, const Vector2 &uvc) {
	Vector3 x, y, t, bt, n, o, p;
	Vector2 u, v;
	float r, w;
	x = b - a;
	y = c - a;
	u = uvb - uva;
	v = uvc - uva;
	r = 1.0f / (u.x * v.y - u.y * v.x);
	t = Vector3(
			((x.x * v.y) - (y.x * u.y)) * r,
			((x.y * v.y) - (y.y * u.y)) * r,
			((x.z * v.y) - (y.z * u.y)) * r);
	bt = Vector3(
			((x.x * v.x) - (y.x * u.x)) * r,
			((x.y * v.x) - (y.y * u.x)) * r,
			((x.y * v.x) - (y.z * u.x)) * r);

	n = a;
	n.normalize();
	o = t - (n * n.dot(t));
	o.normalize();
	p = n.cross(t);
	w = (p.dot(bt) < 0) ? -1.0f : 1.0f;
	tangents.push_back(o.x);
	tangents.push_back(o.y);
	tangents.push_back(o.z);
	tangents.push_back(w);

	n = b;
	n.normalize();
	o = t - (n * n.dot(t));
	o.normalize();
	p = n.cross(t);
	w = (p.dot(bt) < 0) ? -1.0f : 1.0f;
	tangents.push_back(o.x);
	tangents.push_back(o.y);
	tangents.push_back(o.z);
	tangents.push_back(w);

	n = c;
	n.normalize();
	o = t - (n * n.dot(t));
	o.normalize();
	p = n.cross(t);
	w = (p.dot(bt) < 0) ? -1.0f : 1.0f;
	tangents.push_back(o.x);
	tangents.push_back(o.y);
	tangents.push_back(o.z);
	tangents.push_back(w);
}
void MeshData::clear() {
	verts = PoolVector3Array();
	normals = PoolVector3Array();
	uvs = PoolVector2Array();
	tangents = PoolRealArray();
}
} // namespace Voxot