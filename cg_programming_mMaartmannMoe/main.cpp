// main.cpp
//////////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "APP.Initialize.h"
#include "APP.Ball.h"
#include "APP.Paddle.h"
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
	CBall* ball = new CBall();
	ball->SetQuadID(quadID);
	ball->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	ball->SetVelocity(vec3(0.79f, 0.07f, 0.0f));

	// Setup Left Paddle
	CPaddle* paddleLeft = new CPaddle();
	paddleLeft->SetQuadID(quadID);
	paddleLeft->SetPosition(vec3(-1.5f,0.0f,0.0f));
	paddleLeft->SetKeyUp(GLFW_KEY_W);
	paddleLeft->SetKeyDown(GLFW_KEY_S);

	CPaddle* paddleRight = new CPaddle();
	paddleRight->SetQuadID(quadID);
	paddleRight->SetPosition(vec3(1.5f,0.0f,0.0f));
	paddleRight->SetKeyUp(GLFW_KEY_UP);
	paddleRight->SetKeyDown(GLFW_KEY_DOWN);

	/* MAIN GAME LOOP: Loop until the user closes the window or presses ESC */
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get delta time...
		float fDeltaTime = GetDeltaTime();
		#ifdef _DEBUG
			//fprintf(stdout, "Delta Time: %f\n", fDeltaTime);
		#endif	

		// Update phase; i.e. Update()...
		paddleLeft->Update(fDeltaTime);
		paddleRight->Update(fDeltaTime);
		ball->Update(fDeltaTime, paddleLeft, paddleRight);

		// Draw phase:
		ball->Draw(camMain);
		paddleLeft->Draw(camMain);
		paddleRight->Draw(camMain);
		
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