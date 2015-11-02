/**
* This engine is a "wheel" made by myself , the reason why i did this
* is just for study game engine & render architecture.
*
* Author: RaymondTao
* Date: 2015-10-30
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <stdio.h>
#include "Engine/Tools/RayUtils.h"

int main(int argc, char* argv[])
{
	DEBUG_MESSAGE("Engine start", RAY_ERROR);

	GLFWwindow*  window;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	/* Initialize the library */
	if (!glfwInit())
		return 1;
	
	int Major, Minor, Rev;

	glfwGetVersion(&Major, &Minor, &Rev);
	printf("GLFW Version: %d.%d.%d initialized", Major, Minor, Rev);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "Ray Engine", monitor, NULL);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	/* Must be done after glfw is initialized */
	bool glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		glfwTerminate();
		return 1;
	}

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(window))
	{
		/*Render here*/


		/* Swap front and back buffers*/
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}