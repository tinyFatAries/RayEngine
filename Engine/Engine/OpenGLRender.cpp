#include "../Tools/RayUtils.h"
#include "OpenGLRender.h"
#include "Shader.h"
#include "../Math/RayMath.h"

#include <stdio.h>
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
	GLuint VBO;
	/*Vertex Buffer*/
	Vector Vertices[3];
	Vertices[0] = Vector(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	string shaderName("basic");
	ShaderManager::getInstancePtr()->CreateEffect(shaderName);
	ShaderManager::getInstancePtr()->AddVertexShader(shaderName);
	ShaderManager::getInstancePtr()->AddPixelShader(shaderName);
	ShaderManager::getInstancePtr()->SetVS(shaderName, shaderName);
	ShaderManager::getInstancePtr()->SetPS(shaderName, shaderName);
	ShaderManager::getInstancePtr()->LinkShaders(shaderName);
	ShaderManager::getInstancePtr()->EnableShader(shaderName);

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(m_Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		static float scale = 0.0f;

		scale += 0.001f;

		Matrix World;
		
		World.M[0][0] = 1.0f; World.M[0][1] = 0.0f; World.M[0][2] = 0.0f; World.M[0][3] = 0.0f;
		World.M[1][0] = 0.0f; World.M[1][1] = 1.0f; World.M[1][2] = 0.0f; World.M[1][3] = 0.0f;
		World.M[2][0] = 0.0f; World.M[2][1] = 0.0f; World.M[2][2] = 1.0f; World.M[2][3] = 0.0f;
		World.M[3][0] = 0.0f; World.M[3][1] = sinf(scale); World.M[3][2] = 0.0f; World.M[3][3] = 1.0f;

		GLuint gWorldLocaltion = glGetUniformLocation(ShaderManager::getInstancePtr()->GetCurrentProg(), "gWorld");
		glUniformMatrix4fv(gWorldLocaltion, 1, GL_TRUE, &World.M[0][0]);
		
		/*Render here*/
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glDisableVertexAttribArray(0);

		/* Swap front and back buffers*/
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void OpenGLRenderSystem::StopRendering()
{

}