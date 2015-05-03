// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "APP.Initialize.h"
#include "APP.Ball.h"
#include "System.LoadScene.h"
#include "System.Camera.h"
#include "System.Utility.h"

GLFWwindow* window = NULL;

int main() {
	// Initialize GLFW, window, GLEW...
	// Compare with bitwise OR. If they all succeed then this step is skipped.
	if (InitWindowFailed() | InitGlewFailed()) {
		return EXIT_WITH_ERROR;
	}
	
	LoadScene();

	// Setup Ball
	Ball* ball = new Ball();
	ball->SetQuadID(quadID);
	ball->SetPosition(vec3(0));
	ball->SetVelocity(vec3(1.0f, 0.0f, 0.0f));

	/* MAIN GAME LOOP: Loop until the user closes the window or presses ESC */
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get delta time...
		float fDeltaTime = GetDeltaTime();
		#ifdef _DEBUG
			//fprintf(stdout, "Delta Time: %f\n", fDeltaTime);
		#endif	

		// Update phase; i.e. Update()...
		ball->Update(fDeltaTime);

		// Draw phase:
		ball->Draw(camMain);
		// Render the paddle
		mat4 MVPMatrix = camMain->GetProjectionMatrix() * camMain->GetViewMatrix() * RenderQuad(quadID, vec3(-1.0f,0.0f,0.0f), vec3(0.05f, 0.7f,0.0f));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
		// Render the paddle
		MVPMatrix = camMain->GetProjectionMatrix() * camMain->GetViewMatrix() * RenderQuad(quadID, vec3(1.0f,0.0f,0.0f), vec3(0.05f, 0.7f,0.0f));
		glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
		
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