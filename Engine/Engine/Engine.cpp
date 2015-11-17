#include "Engine.h"
#include "../Tools/RayUtils.h"
#include "RenderSystem.h"
#include "../RenderSystem/OpenGL/OpenGLRender.h"
#include "InputManager.h"

#include <string>
using namespace std;

RayEngine::RayEngine() 
	: m_bInitialized(false)
	, m_RenderSystem(nullptr)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "RayEngine Start...");

	m_RenderSystem = new OpenGLRenderSystem(1024, 768, "Ray Engine", false);

	m_InputManager = new InputManager();
}

RayEngine::~RayEngine()
{
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
