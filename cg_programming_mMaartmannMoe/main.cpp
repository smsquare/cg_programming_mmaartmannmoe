// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "APP.Initialize.h"
#include "APP.Ball.h"
#include "APP.Paddle.h"
#include "System.LoadScene.h"
#include "System.Camera.h"
#include "System.Utility.h"
#include "APP.TestObject.h"
#include "APP.Plane.h"
#include "APP.World.h"

GLFWwindow* window = NULL;

int main() {
	// Initialize GLFW, window, GLEW...
	// Compare with bitwise OR. If they all succeed then this step is skipped.
	if (InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}
	
	LoadScene();

	World* world = new World();

	//HACK: POLYGON MODE
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	// Turn off wireframe mode
	//glPolygonMode(GL_FRONT, GL_FILL);

	/* MAIN GAME LOOP: Loop until the user closes the window or presses ESC */
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get delta time...
		float fDeltaTime = GetDeltaTime();


		// Update phase; i.e. Update()...
		//TODO: ADD World Update function
		// Draw phase:
		world->Render(camMain);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

	} while ( // Check if the ESC key was pressed OR the window was closed...
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	glfwTerminate();
	return 0;
}