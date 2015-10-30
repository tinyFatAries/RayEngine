//=============================================================================
// Engine: The base class of the global application object classes.
//=============================================================================

#pragma once
class RayEngine
{
private:
	RayEngine();

public:
	static RayEngine* getInstance() 
	{
		static RayEngine rayEngine;
		return &rayEngine;
	}


	bool Init();
	bool InitWindow();
	void Render();

private:
	bool m_bInitialized;

};

