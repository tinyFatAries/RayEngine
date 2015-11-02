//=============================================================================================
// RenderSystem: The abstract base class of the concrete Render System like DirectX or OpenGL.
//=============================================================================================

#pragma once
#include <string>

enum RenderType 
{ 
	OPENGL, 
	D3D11, 
	OPENGL_ES 
};

class RenderSystem
{
public:
	RenderSystem(RenderType type, std::string sysName)
		: m_RenderType(type)
		, m_SysName(sysName)
	{}
	
	~RenderSystem()
	{}

public:
	virtual void StartRendering() = 0;
	virtual void StopRendering() = 0;
	virtual bool SetParam(int width, int height, std::string name, bool isFullSceen) = 0;

	const RenderType getRenderType() const
	{
		return m_RenderType;
	}

	const std::string getSysname() const
	{
		return m_SysName;
	}

protected:
	virtual bool InitWindow() = 0;
	virtual void RenderOneFrame() = 0;

protected:
	RenderType m_RenderType;
	std::string m_SysName;
};

