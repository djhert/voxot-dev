#ifndef _MYWORLD_H_
#define _MYWORLD_H_

#include "voxot/world.hpp"

class myworld : public Voxot::World {
public:
	myworld(){};
	~myworld(){};

	void Generate() override;

	static void _register_methods();

private:
	static bool registered;
};

#endif