// APP.World.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"
#include "System.Object.h"
#include "APP.Plane.h"

class World {
	public:
		World();
		virtual ~World();

		void Render(Camera* a_camera);
		void Update(Camera* a_camera);
	private:
		Plane* plane;
};
