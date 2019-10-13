#include "chunk.hpp"

namespace Voxot {

Chunk::~Chunk() {
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			delete[] Blocks[x][y];
		}
		delete[] Blocks[x];
	}
	delete[] Blocks;
	delete meshData;
	meshArray.clear();
}

MetaBlock Chunk::AirBlock = { "air", 0 };

String Chunk::toName(const int &x, const int &y, const int &z) {
	std::string out;
	if (std::abs(x) < 10)
		out = "0" + std::to_string(x);
	else
		out = std::to_string(x);

	if (std::abs(y) < 10)
		out = out + "0" + std::to_string(y);
	else
		out = out + std::to_string(y);

	if (std::abs(z) < 10)
		out = out + "0" + std::to_string(z);
	else
		out = out + std::to_string(z);

	return String(out.c_str());
}

void Chunk::_register_methods() {
	register_method("_ready", &Chunk::_ready);
	register_method("_process", &Chunk::_process);
}

void Chunk::_init() {
	staticBody = StaticBody::_new();
	collisionShape = CollisionShape::_new();
	add_child(staticBody);
	staticBody->add_child(collisionShape);

	meshData = new MeshData();
	meshArray = Array();
	collisionMesh = ConcavePolygonShape::_new();

	isDirty = false;
	isUpdating = false;
	Init();
}

void Chunk::_ready() {
	Ready();
}

void Chunk::setup(World *w, const int &posx, const int &posy, const int &posz) {

	_world = w;
	Width = _world->getChunkWidth();
	Height = _world->getChunkHeight();
	Depth = _world->getChunkDepth();

	X = posx;
	Y = posy;
	Z = posz;

	Vector3 pos = Vector3(X, Y, Z);
	Transform t = get_transform();
	t.origin = pos;
	set_transform(t);

	set_name(toName(X, Y, Z));
	staticBody->set_name(get_name());
	collisionShape->set_name(get_name());

	Blocks = new MetaBlock **[Width];
	for (int x = 0; x < Width; x++) {
		Blocks[x] = new MetaBlock *[Height];
		for (int y = 0; y < Height; y++) {
			Blocks[x][y] = new MetaBlock[Depth];
		}
	}

	Generate();
	dirty();
}

void Chunk::_process(double delta) {
	if (isDirty) {
		if (!isUpdating) {
			isUpdating = true;
			isDirty = false;
			Render(this);
		}
	}
	Update(delta);
}

void Chunk::Generate() {
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			for (int z = 0; z < Depth; z++) {
				Blocks[x][y][z] = { "solid", 0 };
			}
		}
	}
}

void Chunk::Render(Chunk *obj) {
	ArrayMesh *mesh = ArrayMesh::_new();

	obj->meshArray.clear();
	obj->meshData->clear();

	for (int x = 0; x < obj->Width; x++) {
		for (int y = 0; y < obj->Height; y++) {
			for (int z = 0; z < obj->Depth; z++) {
				BlockBin::instance().Get(obj->Blocks[x][y][z].name.c_str())->Draw(obj, obj->meshData, x, y, z);
			}
		}
	}

	obj->meshArray.resize(ArrayMesh::ARRAY_MAX);
	obj->meshArray[ArrayMesh::ARRAY_VERTEX] = obj->meshData->verts;
	obj->meshArray[ArrayMesh::ARRAY_TEX_UV] = obj->meshData->uvs;
	obj->meshArray[ArrayMesh::ARRAY_NORMAL] = obj->meshData->normals;
	obj->meshArray[ArrayMesh::ARRAY_TANGENT] = obj->meshData->tangents;

	mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, obj->meshArray);
	obj->set_mesh(mesh);

	Ref<SpatialMaterial> mat = obj->_world->GetMaterial("default");
	if (!mat.is_valid()) {
		Godot::print("material not good");
	} else {
		obj->set_surface_material(0, mat);
	}
	obj->collisionMesh->set_faces(obj->meshData->verts);
	obj->collisionShape->set_shape(obj->collisionMesh);

	obj->isUpdating = false;
}

Block *Chunk::GetBlock(const int &x, const int &y, const int &z) {
	if (inBounds(x, y, z))
		return BlockBin::instance().Get(Blocks[x][y][z].name.c_str());
	else
		return BlockBin::instance().Get("air");
}

bool Chunk::DeleteBlock(const int &x, const int &y, const int &z) {
	if (isUpdating.load()) {
		return false;
	}
	if (inBounds(x, y, z)) {
		if (Blocks[x][y][z] != AirBlock) {
			dirty();
			Blocks[x][y][z] = { "air", 0 };
			return true;
		}
	}
	return false;
}

bool Chunk::inBounds(const int &x, const int &y, const int &z) {
	if (x >= 0 && x < Width) {
		if (y >= 0 && y < Height) {
			if (z >= 0 && z < Depth) {
				return true;
			}
		}
	}
	return false;
}

} // namespace Voxot