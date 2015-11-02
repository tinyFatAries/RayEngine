//=============================================================================
// Engine: The base class of the global application object classes.
//=============================================================================

#pragma once

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

};

