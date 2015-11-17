//=============================================================================
// Engine: The base class of the global application object classes.
//=============================================================================

#pragma once

class RenderSystem;
class ShaderManager;
class InputManager;
	
class RayEngine
{
private:
	RayEngine();
	~RayEngine();

public:
	static RayEngine* getInstance() 
	{
		static RayEngine rayEngine;
		return &rayEngine;
	}


	bool Start();
	bool InitRenderSystem();
	void Render();

private:
	bool m_bInitialized;
	RenderSystem* m_RenderSystem;
	InputManager* m_InputManager;
};

