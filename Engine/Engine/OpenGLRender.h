//=============================================================================================
// RenderSystem: The abstract base class of the concrete Render System like DirectX or OpenGL.
//=============================================================================================

#pragma once
#include "RenderSystem.h"
#include "RayTimer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera;

class OpenGLRenderSystem : public RenderSystem
{
public:
	OpenGLRenderSystem();
	OpenGLRenderSystem(int width, int height, std::string name, bool isFullScreen);
	~OpenGLRenderSystem();

	virtual bool InitWindow();
	virtual void StartRendering();
	virtual void StopRendering();
	virtual bool SetParam(int width, int height, std::string name, bool isFullSceen);

	GLFWwindow* GetWindowHandler();

protected:
	virtual void RenderOneFrame();
	virtual void CalculateFrameStats();
	virtual void SetupShaders();
	virtual void SetupVertexBuffer();
	virtual void SetupIndexBuffer();
	virtual void SetupTexure();
	virtual void SetupLights();


private:
	bool m_bInitialized;
	bool m_bFullScreen;
	int m_Width;
	int m_Height;

	GLFWwindow* m_Window;
	GLFWmonitor* m_Monitor;

	bool m_SysPaused;
	RayTimer m_Timer;

	GLuint VBO, IBO;

	Camera *m_Camera;
};

