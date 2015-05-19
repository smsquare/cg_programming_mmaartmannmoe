//  APP.World.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.World.h"
#include "System.Mesh.h"

World::World() {
	this->plane = new Plane(10, 10);
	this->plane->SetScale(vec3(0.05f));
	
	// load world...
	ifstream myFile(LEVEL_0);
	char buffer[256];
	char path[256];

	if (myFile.is_open()) {
		string line;
		unsigned char len = 0;

		while (getline(myFile, line)) {
			line.copy(buffer, len = line.length());
			buffer[len] = '\0';
			
			unsigned char commaLen = m_FindChar(buffer, ',');
			
			// Found textures
			if (commaLen > 0) {
				strcpy(path, buffer);
				path[commaLen - 1] = '\0';
			}

			// load textures...

		}
		myFile.close();
	} else cout << "Unable to open file...";
	
}

World::~World() {
	delete plane;
	plane = NULL;
}

void World::Render(Camera* a_camera) {
	plane->Render(a_camera);
}

void World::Update(Camera* a_camera) {
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.x += 0.1f;
		worldPos.x += 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.x -= 0.1f;
		worldPos.x -= 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.y += 0.1f;
		worldPos.y += 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.y -= 0.1f;
		worldPos.y -= 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}

	if (glfwGetKey(window, GLFW_KEY_W)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.z += 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
	
	if (glfwGetKey(window, GLFW_KEY_S)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.z -= 0.1f;
		if (pos.z < 0.5) {
			pos.z = 0.5;
		}
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
}

// Search a buffer for a character: a_c
unsigned char World::m_FindChar(const char* a_buffer, const char& a_c) {
	//TODO: Search for char a_c, if found, return true...
	char* value = (char*)a_buffer;
	
	unsigned char len = 0;

	while (value != '\0') {
		++len;
		if (*(value++) == a_c) {
			return len;
		}

	}

	return len = 0;
}