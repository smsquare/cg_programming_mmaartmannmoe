//  APP.World.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.World.h"

World::World() {
	this->plane = new Plane(2, 2);
}

World::~World() {
	delete plane;
	plane = NULL;
}

void World::Render(Camera* a_camera) {
	plane->Render(a_camera);
}