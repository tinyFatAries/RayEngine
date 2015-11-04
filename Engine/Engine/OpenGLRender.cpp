#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <stdio.h>

#include "../Tools/RayUtils.h"
#include "../Math/RayMath.h"
#include "OpenGLRender.h"


using namespace std;

/**
	default constructor
**/
OpenGLRenderSystem::OpenGLRenderSystem()
	: RenderSystem(RenderType::OPENGL, "OpenGL Render System")
	, m_bInitialized(false)
	, m_bFullScreen(false)
	, m_Width(800)
	, m_Height(600)
	, m_Window(nullptr)
	, m_Monitor(nullptr)
{
	InitWindow();
}

/**
	param list constructor
**/
OpenGLRenderSystem::OpenGLRenderSystem(int width, int height, string name, bool isFullScreen)
	: RenderSystem(RenderType::OPENGL, name)
	, m_bInitialized(false) 
	, m_bFullScreen(false)
	, m_Width(width)
	, m_Height(height)
	, m_Window(nullptr)
	, m_Monitor(nullptr)
{
	InitWindow();
}

/*
	destructor
*/
OpenGLRenderSystem::~OpenGLRenderSystem()
{

}


/**
	init opengl render window
**/
bool OpenGLRenderSystem::InitWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return 1;

	int Major, Minor, Rev;

	glfwGetVersion(&Major, &Minor, &Rev);
	DEBUG_MESSAGE(RAY_MESSAGE, "GLFW Version: %d.%d.%d initialized", Major, Minor, Rev);

	if (m_bFullScreen)
	{
		m_Monitor = glfwGetPrimaryMonitor();
	}

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(1024, 768, "Ray Engine", m_Monitor, NULL);
	if (!m_Window)
	{
		DEBUG_MESSAGE(RAY_ERROR, "glfwCreateWindow failed, exited unexcepted!");
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);
	
	/* Must be done after glfw is initialized */
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		DEBUG_MESSAGE(RAY_ERROR, "Init failed, exited unexcepted!");
		glfwTerminate();
		return false;
	}

	return true;
}

bool OpenGLRenderSystem::SetParam(int width, int height, std::string name, bool isFullSceen)
{
	m_Width = width;
	m_Height = height;
	m_SysName = name;
	m_bFullScreen = isFullSceen;
	return true;
}

void OpenGLRenderSystem::RenderOneFrame()
{

}

void OpenGLRenderSystem::StartRendering()
{
	/*Vertex Buffer*/
	Vector Vertices[1];
	Vertices[0].Set(0.0f, 0.0f, 0.0f);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(m_Window))
	{
		/*Render here*/
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_POINTS, 0, 1);
		/* Swap front and back buffers*/
		glfwSwapBuffers(m_Window);
		glDisableVertexAttribArray(0);
		/* Poll for and process events */
		glfwPollEvents();
	}
}

void OpenGLRenderSystem::StopRendering()
{

}