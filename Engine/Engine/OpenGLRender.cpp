#include "OpenGLRender.h"
#include "../Tools/RayUtils.h"
using namespace std;

/* static member initialize */
template<> OpenGLRenderSystem* Singleton<OpenGLRenderSystem>::m_pSingleton = nullptr;

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

#ifdef DEBUG_MODE
	glfwGetVersion(&Major, &Minor, &Rev);
	printf("GLFW Version: %d.%d.%d initialized", Major, Minor, Rev);
#endif

	if (m_bFullScreen)
	{
		m_Monitor = glfwGetPrimaryMonitor();
	}

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(1024, 768, "Ray Engine", m_Monitor, NULL);
	if (!m_Window)
	{
		DEBUG_MESSAGE("glfwCreateWindow failed, exited unexcepted!", RAY_ERROR);
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);
	
	/* Must be done after glfw is initialized */
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		DEBUG_MESSAGE("Init failed, exited unexcepted!", RAY_ERROR);
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


}

void OpenGLRenderSystem::StopRendering()
{

}