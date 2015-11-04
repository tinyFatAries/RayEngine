//=============================================================================================
// RenderSystem: The base class of the concrete Render System like DirectX or OpenGL.
//=============================================================================================

#pragma once
#include "Singleton.h"
#include <string>

enum RenderType 
{ 
	OPENGL, 
	D3D11, 
	OPENGL_ES 
};

class RenderSystem : public Singleton<RenderSystem>
{
public:
	RenderSystem() {}

	RenderSystem(RenderType type, std::string sysName)
		: m_RenderType(type)
		, m_SysName(sysName)
	{}
	
	~RenderSystem()
	{}

protected:
	virtual void RenderOneFrame() {}
	//some render state settings
	virtual void SetShader() {}
	virtual void SetRenderQueue() {}
	virtual void SetVertexBuffer() {}
	virtual void SetIndexBuffer() {}
	virtual void SetTexture() {}

public:
	virtual bool InitWindow() { return true; }
	virtual void StartRendering() {}
	virtual void StopRendering() {}
	virtual bool SetParam(int width, int height, std::string name, bool isFullSceen) { return true; }

	const RenderType getRenderType() const
	{
		return m_RenderType;
	}

	const std::string getSysname() const
	{
		return m_SysName;
	}

protected:
	RenderType m_RenderType;
	std::string m_SysName;
};



