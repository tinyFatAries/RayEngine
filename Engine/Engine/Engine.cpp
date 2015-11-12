#include "Engine.h"
#include "RenderSystem.h"
#include "OpenGLRender.h"
#include "InputManager.h"
#include "Shader.h"
#include "../Tools/RayUtils.h"

#include <string>
using namespace std;

RayEngine::RayEngine() 
	: m_bInitialized(false)
	, m_RenderSystem(nullptr)
	, m_ShaderManager(nullptr)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "RayEngine Start...");

	m_RenderSystem = new OpenGLRenderSystem(1024, 768, "Ray Engine", false);

	m_ShaderManager = new ShaderManager();

	m_InputManager = new InputManager();
}

RayEngine::~RayEngine()
{
	R_DELETE(m_ShaderManager);
	R_DELETE(m_RenderSystem);
	R_DELETE(m_InputManager);
}

bool RayEngine::Start()
{
	RenderSystem::getInstancePtr()->StartRendering();
	return true;
}

bool RayEngine::InitRenderSystem()
{
	return true;
}

void RayEngine::Render()
{

}
