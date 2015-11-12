#pragma once

#include "../Engine/InputManager.h"

class Camera;
class CameraController : public InputListener
{
public:
	CameraController() 
		: m_Camera(nullptr) {}

	virtual ~CameraController() {}

	virtual void AttachTo(Camera* cam) {}

	virtual void Update(float deltaTime) {}

protected:
	Camera* m_Camera;
};