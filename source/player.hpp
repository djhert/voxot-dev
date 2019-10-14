#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Camera.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <InputEventMouseMotion.hpp>
#include <KinematicBody.hpp>
#include <NodePath.hpp>
#include <RayCast.hpp>
#include <SceneTree.hpp>
#include <Spatial.hpp>
#include <Viewport.hpp>

#include "voxot/metablock.hpp"
#include "voxot/world.hpp"

using namespace godot;

class Player : public KinematicBody {
	GDNATIVE_CLASS(Player, KinematicBody)

public:
	void _input(Variant);
	void _physics_process(double);

	static double deg2rad(double);

protected:
	double speed;
	double acceleration;
	double gravity;
	double jump_power;
	double flyspeed;
	double mouse_sensitivity;

	Spatial *_head;
	Camera *_camera;
	RayCast *_raycast;
	Voxot::World *_world;

	Vector3 _velocity;
	double _deltaXRot;

	static Vector3 UP;

	bool isFlying;
	double flyInputTime;
};

#endif