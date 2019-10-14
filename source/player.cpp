#include "player.hpp"

REGISTER_CLASS(Player);

Player::Player() {}
Player::~Player() {}

Vector3 Player::UP = Vector3(0, 1, 0);

double Player::deg2rad(double input) {
	return input * (M_PI / 180);
}

void Player::_register_methods() {
	register_property<Player, double>("Speed", &Player::speed, 10.0);
	register_property<Player, double>("Acceleration", &Player::acceleration, 5.0);
	register_property<Player, double>("Gravity", &Player::gravity, -0.98);
	register_property<Player, double>("Jump Power", &Player::jump_power, 30.0);
	register_property<Player, double>("Mouse Sensitivity", &Player::mouse_sensitivity, 0.3f);
	register_property<Player, double>("Fly Speed", &Player::flyspeed, 20.0);

	GDNATIVE_REGISTER(Player)
	register_method("_input", &Player::_input);
	register_method("_physics_process", &Player::_physics_process);
}

void Player::_init() {
	speed = 10.0f;
	acceleration = 5.0f;
	gravity = -0.98f;
	jump_power = 30.0f;
	mouse_sensitivity = 0.3f;
	flyspeed = 20.0f;
}

void Player::_ready() {
	_head = Object::cast_to<Spatial>(get_child(0));
	_camera = Object::cast_to<Camera>(_head->get_child(0));
	_raycast = Object::cast_to<RayCast>(_camera->get_child(0));

	const NodePath &path = NodePath("../World");
	_world = Node::cast_to<Voxot::World>(get_node(path));

	Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
	isFlying = true;
	flyInputTime = 1;
}

void Player::_process(double delta) {
	if (Input::get_singleton()->is_action_just_pressed("ui_cancel")) {
		get_tree()->quit();
	}
	if (Input::get_singleton()->is_action_just_pressed("l_click")) {
		if (_raycast->is_colliding()) {
			_world->AddBlock(_raycast->get_collision_point() + _raycast->get_collision_normal(),
					{ "solid", 0 });
		}
	} else if (Input::get_singleton()->is_action_just_pressed("r_click")) {
		if (_raycast->is_colliding()) {
			Vector3 temp = _raycast->get_collision_point();
			int final = _raycast->get_collision_normal().x + _raycast->get_collision_normal().y + _raycast->get_collision_normal().z;
			if (final > 0)
				temp -= _raycast->get_collision_normal();
			_world->DeleteBlock(temp);
		}
	}
}

void Player::_physics_process(double delta) {
	Basis basis = _head->get_global_transform().get_basis();
	Vector3 dir;

	if (flyInputTime < 0.25)
		flyInputTime += delta;
	else
		flyInputTime = 1;

	if (Input::get_singleton()->is_action_pressed("ui_up")) {
		dir -= basis.z;
	} else if (Input::get_singleton()->is_action_pressed("ui_down")) {
		dir += basis.z;
	}

	if (Input::get_singleton()->is_action_pressed("ui_left")) {
		dir -= basis.x;
	} else if (Input::get_singleton()->is_action_pressed("ui_right")) {
		dir += basis.x;
	}

	dir.normalize();

	_velocity = _velocity.linear_interpolate(dir * speed, acceleration * delta);

	if (!isFlying) {
		_velocity.y += gravity;
		if (Input::get_singleton()->is_action_just_pressed("ui_jump")) {
			if (flyInputTime < 0.25) {
				isFlying = true;
			}
			if (is_on_floor()) {
				_velocity.y += jump_power;
				flyInputTime = 0;
			}
		}
	} else {
		if (Input::get_singleton()->is_action_just_pressed("ui_jump")) {
			if (flyInputTime == 1) {
				flyInputTime = 0;
			} else {
				isFlying = false;
			}
		}
		if (Input::get_singleton()->is_action_pressed("ui_page_up")) {
			_velocity.y += flyspeed * delta;
		} else if (Input::get_singleton()->is_action_pressed("ui_page_down")) {
			_velocity.y -= flyspeed * delta;
		}
	}

	_velocity = move_and_slide(_velocity, UP);
}

void Player::_input(Variant event) {
	InputEvent *e = InputEvent::cast_to<InputEvent>(event);
	if (e->is_class("InputEventMouseMotion")) {
		InputEventMouseMotion *mouse = InputEvent::cast_to<InputEventMouseMotion>(event);

		_head->rotate_y(deg2rad(-mouse->get_relative().x * mouse_sensitivity));

		double deltaRot = mouse->get_relative().y * mouse_sensitivity;
		if (_deltaXRot + deltaRot > -90 && _deltaXRot + deltaRot < 90) {
			_camera->rotate_x(deg2rad(-deltaRot));
			_deltaXRot += deltaRot;
		}
	}
}