#ifndef _MYWORLD_H_
#define _MYWORLD_H_

#include <gdutil/gdnregistry.hpp>
#include <voxot/world.hpp>

class myworld : public Voxot::World {
	GDNATIVE_CHILD_CLASS(myworld, Voxot::World)
public:
	void Generate() override;
};

#endif