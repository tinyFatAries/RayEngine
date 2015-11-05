#include "Engine.h"
#include "RenderSystem.h"
#include "OpenGLRender.h"
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
	DEBUG_MESSAGE(RAY_MESSAGE, "RenderSystem Start...");

	m_ShaderManager = new ShaderManager();
	DEBUG_MESSAGE(RAY_MESSAGE, "ShaderManager Start...");
}

RayEngine::~RayEngine()
{

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
