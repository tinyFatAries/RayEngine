//=============================================================================================
// RenderSystem: The abstract base class of the concrete Render System like DirectX or OpenGL.
//=============================================================================================

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include "RenderSystem.h"
#include "Singleton.h"

#include <stdio.h>

class OpenGLRenderSystem : public Singleton<OpenGLRenderSystem>, public RenderSystem
{
public:
	OpenGLRenderSystem();
	OpenGLRenderSystem(int width, int height, std::string name, bool isFullScreen);
	~OpenGLRenderSystem();

	virtual void StartRendering();
	virtual void StopRendering();
	virtual bool SetParam(int width, int height, std::string name, bool isFullSceen);

protected:
	virtual bool InitWindow();
	virtual void RenderOneFrame();


private:
	bool m_bInitialized;
	bool m_bFullScreen;
	int m_Width;
	int m_Height;

	GLFWwindow* m_Window;
	GLFWmonitor* m_Monitor;

};

