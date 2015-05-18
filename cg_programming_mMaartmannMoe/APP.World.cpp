//  APP.World.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.World.h"
#include "System.Mesh.h"

World::World() {
	this->plane = new Plane(100, 100);
	this->plane->SetScale(vec3(0.05f));
}

World::~World() {
	delete plane;
	plane = NULL;
}

void World::Render(Camera* a_camera) {
	plane->Render(a_camera);
}

void World::Update(Camera* a_camera) {
	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.x += 0.1f;
		worldPos.x += 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.x -= 0.1f;
		worldPos.x -= 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		vec3 pos = a_camera->GetPosition();
		vec3 worldPos = a_camera->GetWorldOrigin();
		pos.y += 0.1f;
		worldPos.y += 0.1f;
		a_camera->SetViewMatrix(pos, worldPos, vec3(0,1,0));
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) {
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