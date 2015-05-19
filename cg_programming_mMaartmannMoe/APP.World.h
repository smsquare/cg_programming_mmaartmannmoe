// APP.World.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"
#include "System.Object.h"
#include "APP.Plane.h"

#define LEVEL_0 "Relevel0.txt"

class World {
	public:
		World();
		virtual ~World();

		void Render(Camera* a_camera);
		void Update(Camera* a_camera);
	private:
		Plane* plane;
		unsigned char* loadedFile;
		const char* loadedLevel;
		unsigned char m_FindChar(const char* a_buffer, const char& a_c);
};
