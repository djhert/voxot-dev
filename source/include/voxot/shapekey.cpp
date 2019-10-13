#include "shapekey.hpp"

namespace Voxot {
const Vector2 ShapeKey::key[25] = {
	Vector2(0.0f, 0.0f), // 0 Bottom Left
	Vector2(0.25f, 0.0f), //1
	Vector2(0.5f, 0.0f), //2
	Vector2(0.75f, 0.0f), //3
	Vector2(1.0f, 0.0f), //4 Bottom Right

	Vector2(0.0f, 0.25f), //5
	Vector2(0.25f, 0.25f), //6
	Vector2(0.5f, 0.25f), //7
	Vector2(0.75f, 0.25f), //8
	Vector2(1.0f, 0.25f), //9

	Vector2(0.0f, 0.5f), //10
	Vector2(0.25f, 0.5f), //11
	Vector2(0.5f, 0.5f), //12
	Vector2(0.75f, 0.5f), //13
	Vector2(1.0f, 0.5f), //14

	Vector2(0.0f, 0.75f), //15
	Vector2(0.25f, 0.75f), //16
	Vector2(0.5f, 0.75f), //17
	Vector2(0.75f, 0.75f), //18
	Vector2(1.0f, 0.75f), //19

	Vector2(0.0f, 1.0f), //20 Top Left
	Vector2(0.25f, 1.0f), //21
	Vector2(0.5f, 1.0f), //22
	Vector2(0.75f, 1.0f), //23
	Vector2(1.0f, 1.0f) //24 Top Right
};

ShapeKey::ShapeKey(){};

ShapeKey::~ShapeKey() {
}

ShapeKey &ShapeKey::Get() {
	static ShapeKey instance;
	return instance;
}

Vector3 ShapeKey::At(const int &x, const int &y, const int &z,
		const int &index, const float &height) {
	return Vector3(key[index].x + x, y + height, key[index].y + z);
}

} // namespace Voxot