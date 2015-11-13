#include "OpenGLRender.h"
#include "Shader.h"
#include "../Tools/RayUtils.h"
#include "../Math/RayMath.h"
#include "../Camera/Camera.h"
#include "../Camera/FreeCameraController.h"

#include <stdio.h>
using namespace std;

struct Vertex
{
	Vector positon;
	Vector4 Color;
};
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
	, m_SysPaused(false)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "OpenGL RenderSystem Start...");
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
	, m_SysPaused(false)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "OpenGL RenderSystem Start Resolution %d x %d...", width, height);
	InitWindow();
}

/*
	destructor
*/
OpenGLRenderSystem::~OpenGLRenderSystem()
{
	R_DELETE(m_Camera);
	DEBUG_MESSAGE(RAY_MESSAGE, "Unload OpenGL RenderSystem...");
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
	m_Window = glfwCreateWindow(m_Width, m_Height, "Ray Engine", m_Monitor, NULL);
	if (!m_Window)
	{
		DEBUG_MESSAGE(RAY_ERROR, "glfwCreateWindow failed, exited unexcepted!");
		glfwTerminate();
		return false;
	}
	m_WindowHandle = (void*)m_Window;

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
	glClear(GL_COLOR_BUFFER_BIT);

	static float scale = 0.0f;

	scale += 0.003f;

	Matrix World, World2, World3;
	
//	World.M[0][0] = 1.0f;		  World.M[0][1] = 0.0f;		    World.M[0][2] = 0.0f;		 World.M[0][3] = 0.0f;
//	World.M[1][0] = 0.0f;		  World.M[1][1] =cosf(scale);   World.M[1][2] =sinf(scale) ; World.M[1][3] = 0.0f;
//	World.M[2][0] = 0.0f;		  World.M[2][1] = -sinf(scale); World.M[2][2] = cosf(scale); World.M[2][3] = 0.0f;
//	World.M[3][0] = 0.0f;		  World.M[3][1] = 0.0f;		    World.M[3][2] = 0.0f;		 World.M[3][3] = 2.0f;

	World2.M[0][0] = cosf(scale);  World2.M[0][1] = 0.0f; World2.M[0][2] = -sinf(scale); World2.M[0][3] = 0.0f;
	World2.M[1][0] = 0.0f;	       World2.M[1][1] = 1.0f; World2.M[1][2] = 0.0f;		 World2.M[1][3] = 0.0f;
	World2.M[2][0] = sinf(scale);  World2.M[2][1] = 0.0f; World2.M[2][2] = cosf(scale);  World2.M[2][3] = 0.0f;
	World2.M[3][0] = 0.0f;		   World2.M[3][1] = 0.0f; World2.M[3][2] = 0.0f;		 World2.M[3][3] = 2.0f;

//	World3.M[0][0] = cosf(scale);  World3.M[0][1] = sinf(scale);  World3.M[0][2] = 0.0f;  World3.M[0][3] = 0.0f;
//	World3.M[1][0] = -sinf(scale);  World3.M[1][1] = cosf(scale); World3.M[1][2] = 0.0f;  World3.M[1][3] = 0.0f;
//	World3.M[2][0] = 0.0f;		   World3.M[2][1] = 0.0f;		  World3.M[2][2] = 1.0f;  World3.M[2][3] = 0.0f;
//	World3.M[3][0] = 0.0f;		   World3.M[3][1] = 0.0f;		  World3.M[3][2] = 0.0f;  World3.M[3][3] = 2.0f;

	World.M[0][0] = 1.0f;		  World.M[0][1] = 0.0f;		    World.M[0][2] = 0.0f;		 World.M[0][3] = 0.0f;
	World.M[1][0] = 0.0f;		  World.M[1][1] = 1.0f;         World.M[1][2] = 0.0f;        World.M[1][3] = 0.0f;
	World.M[2][0] = 0.0f;		  World.M[2][1] = 0.0f;		    World.M[2][2] = 1.0f;	     World.M[2][3] = 0.0f;
	World.M[3][0] = 1.0f;		  World.M[3][1] = 0.0f;		    World.M[3][2] = 2.0f*sinf(scale);		 World.M[3][3] = 4.0f;

	m_Camera->Update(m_Timer.DeltaTime());
	World2*= m_Camera->GetViewProj();

	GLuint gWorldLocaltion = glGetUniformLocation(ShaderManager::getInstancePtr()->GetCurrentProg(), "gWorld");
	glUniformMatrix4fv(gWorldLocaltion, 1, GL_TRUE, &World2.M[0][0]);
	
	/*Render here*/
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	/* Swap front and back buffers*/
	glfwSwapBuffers(m_Window);

	/* Poll for and process events */
	glfwPollEvents();
}

void OpenGLRenderSystem::StartRendering()
{
	SetupVertexBuffer();
	SetupIndexBuffer();
	SetupShaders();
	SetupTexure();
	SetupLights();

	m_Camera = new Camera();
	m_Camera->SetProjParameters(m_Width*1.0f / m_Height, 45, 1, 1000);
	m_Camera->Project(Perspective);
	m_Camera->SetPosition(Vector(2.0f, 2.0f, 2.0f));
	m_Camera->LookAt(Vector(0.0f, 0.0f, 0.0f));
	CameraController* controller = new FreeCameraController();
	m_Camera->SetController(controller);

	m_Timer.Reset();
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(m_Window))
	{
		m_Timer.Tick();

		if (!m_SysPaused)
		{
			CalculateFrameStats();
			RenderOneFrame();
		}
		else
		{
			;
		}
	}
}

void OpenGLRenderSystem::StopRendering()
{

}

void OpenGLRenderSystem::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		printf("FPS %.2f\n", fps);
	
		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void OpenGLRenderSystem::SetupVertexBuffer()
{
	/*Vertex Buffer*/
	Vertex Vertices[8];
	Vertices[0] = { Vector(-1.0f, -1.0f, -1.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertices[1] = { Vector(-1.0f, 1.0f, -1.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f) };
	Vertices[2] = { Vector(1.0f, 1.0f, -1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f) };
	Vertices[3] = { Vector(1.0f, -1.0f, -1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f) };
	Vertices[4] = { Vector(-1.0f, -1.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f) };
	Vertices[5] = { Vector(-1.0f, 1.0f, 1.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f) };
	Vertices[6] = { Vector(1.0f, 1.0f, 1.0f), Vector4(0.0f, 1.0f, 1.0f, 1.0f) };
	Vertices[7] = { Vector(1.0f, -1.0f, 1.0f), Vector4(1.0f, 0.0f, 1.0f, 1.0f) };

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


void OpenGLRenderSystem::SetupIndexBuffer()
{
	uint32 Indices[] = {
		//back face
		0, 1, 2,
		0, 2, 3,
		//front face
		4, 6, 5,
		4, 7, 6,
		//left face
		4, 5, 1,
		4, 1, 0,
		//right face
		3, 2, 6,
		3, 6, 7,
		//top face
		1, 5, 6,
		1, 6, 2,
		//bottom face
		4, 0, 3,
		4, 3, 7
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}


void OpenGLRenderSystem::SetupTexure()
{

}


void OpenGLRenderSystem::SetupLights()
{

}

void OpenGLRenderSystem::SetupShaders()
{
	ShaderManager* shaderManager = ShaderManager::getInstancePtr();
	string shaderName("basic");
	shaderManager->CreateEffect(shaderName);
	shaderManager->AddVertexShader(shaderName);
	shaderManager->AddPixelShader(shaderName);
	shaderManager->SetVS(shaderName, shaderName);
	shaderManager->SetPS(shaderName, shaderName);
	shaderManager->LinkShaders(shaderName);
	shaderManager->EnableShader(shaderName);
}

GLFWwindow* OpenGLRenderSystem::GetWindowHandler()
{
	return m_Window;
}
