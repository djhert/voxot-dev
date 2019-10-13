#include "blocksolid.hpp"

namespace Voxot {

const MetaBlock BlockSolid::Block = { "solid", 0 };

BlockSolid::BlockSolid() {
}

BlockSolid::~BlockSolid() {}

const bool BlockSolid::isVisible(const Direction &d) {
	return true;
}

const bool BlockSolid::isSolid(const Direction &d) {
	return true;
}

void BlockSolid::Draw(Chunk *chunk, MeshData *data,
		const int &x, const int &y, const int &z) {
	UVTile Tile;

	if (!chunk->GetBlock(x, y, z - 1)->isSolid(South)) {
		FaceNorth(data, x, y, z);
	}
	if (!chunk->GetBlock(x, y, z + 1)->isSolid(North)) {
		FaceSouth(data, x, y, z);
	}
	if (!chunk->GetBlock(x, y + 1, z)->isSolid(Down)) {
		FaceUp(data, x, y, z);
	}
	if (!chunk->GetBlock(x, y - 1, z)->isSolid(Up)) {
		FaceDown(data, x, y, z);
	}
	if (!chunk->GetBlock(x - 1, y, z)->isSolid(East)) {
		FaceWest(data, x, y, z);
	}
	if (!chunk->GetBlock(x + 1, y, z)->isSolid(West)) {
		FaceEast(data, x, y, z);
	}
}

void BlockSolid::FaceUp(MeshData *data, const int &x, const int &y, const int &z) {
	UVTile Tile = FaceUV(Up);
	data->UVSquare(
			ShapeKey::Get().At(x, y, z, 0, 1.0f),
			ShapeKey::Get().At(x, y, z, 4, 1.0f),
			ShapeKey::Get().At(x, y, z, 20, 1.0f),
			ShapeKey::Get().At(x, y, z, 24, 1.0f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - 0.01f));
}

void BlockSolid::FaceDown(MeshData *data, const int &x, const int &y, const int &z) {
	UVTile Tile = FaceUV(Down);
	data->UVSquare(
			ShapeKey::Get().At(x, y, z, 20, 0.0f),
			ShapeKey::Get().At(x, y, z, 24, 0.0f),
			ShapeKey::Get().At(x, y, z, 0, 0.0f),
			ShapeKey::Get().At(x, y, z, 4, 0.0f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - 0.01f));
}

void BlockSolid::FaceNorth(MeshData *data, const int &x, const int &y, const int &z) {
	UVTile Tile = FaceUV(North);

	data->UVSquare(
			ShapeKey::Get().At(x, y, z, 4, 0.0f),
			ShapeKey::Get().At(x, y, z, 4, 1.0f),
			ShapeKey::Get().At(x, y, z, 0, 0.0f),
			ShapeKey::Get().At(x, y, z, 0, 1.0f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - 0.01f));
}

void BlockSolid::FaceSouth(MeshData *data, const int &x, const int &y, const int &z) {
	UVTile Tile = FaceUV(South);

	data->UVSquare(
			ShapeKey::Get().At(x, y, z, 20, 0.0f),
			ShapeKey::Get().At(x, y, z, 20, 1.0f),
			ShapeKey::Get().At(x, y, z, 24, 0.0f),
			ShapeKey::Get().At(x, y, z, 24, 1.0f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - 0.01f));
}

void BlockSolid::FaceWest(MeshData *data, const int &x, const int &y, const int &z) {
	UVTile Tile = FaceUV(West);

	data->UVSquare(
			ShapeKey::Get().At(x, y, z, 0, 0.0f),
			ShapeKey::Get().At(x, y, z, 0, 1.0f),
			ShapeKey::Get().At(x, y, z, 20, 0.0f),
			ShapeKey::Get().At(x, y, z, 20, 1.0f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - 0.01f));
}

void BlockSolid::FaceEast(MeshData *data, const int &x, const int &y, const int &z) {
	UVTile Tile = FaceUV(East);

	data->UVSquare(
			ShapeKey::Get().At(x, y, z, 24, 0.0f),
			ShapeKey::Get().At(x, y, z, 24, 1.0f),
			ShapeKey::Get().At(x, y, z, 4, 0.0f),
			ShapeKey::Get().At(x, y, z, 4, 1.0f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - World::tileSize + 0.01f),
			Vector2((Tile.X * World::tileSize) - World::tileSize + 0.01f,
					(Tile.Y * World::tileSize) - 0.01f),
			Vector2((Tile.X * World::tileSize) - 0.01f,
					(Tile.Y * World::tileSize) - 0.01f));
}

UVTile BlockSolid::FaceUV(const Direction &d) {
	return { 1, 2 };
}
} // namespace Voxot