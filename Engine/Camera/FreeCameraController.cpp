#include "FreeCameraController.h"
#include "../Tools/RayUtils.h"
#include "../Math/RayMath.h"
#include <GLFW/glfw3.h>

FreeCameraController::FreeCameraController()
	: m_bMoveFoward(false)
	, m_bMoveBack(false)
	, m_bMoveLeft(false)
	, m_bMoveRight(false)
	, m_bMoveUp(false)
	, m_bMoveDown(false)
	, m_Speed(0.0f)
	, m_AccSpeed(5.0f)
	, m_MaxSpeed(5.0f)
{
	InputManager::getInstancePtr()->AddListener(this);
}

FreeCameraController::~FreeCameraController()
{
	InputManager::getInstancePtr()->RemoveListener(this);
}

void FreeCameraController::HandleKeyPress(int key, int scancode, int action, int mods)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "key pressed key:%d scancode:%d action:%d mods:%d", key, scancode, action, mods);
	switch (key)
	{
	case GLFW_KEY_W:
		m_bMoveFoward = (action == GLFW_PRESS) ? true : false;
		break;
	case GLFW_KEY_A:
		m_bMoveLeft = (action == GLFW_PRESS) ? true : false;
		break;
	case GLFW_KEY_S:
		m_bMoveBack = (action == GLFW_PRESS) ? true : false;
		break;
	case GLFW_KEY_D:
		m_bMoveRight = (action == GLFW_PRESS) ? true : false;
	case GLFW_KEY_PAGE_UP:
		m_bMoveUp = (action == GLFW_PRESS) ? true : false;
		break;
	case GLFW_KEY_PAGE_DOWN:
		m_bMoveDown = (action == GLFW_PRESS) ? true : false;
		break;
	default:
		break;
	}
}

void FreeCameraController::HandleMouseClick(int button, int action, int mode)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "mouse clicked button:%d action:%d mods:%d", button, action, mode);
}

void FreeCameraController::HandleMouseMove(double x, double y)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "mouse move x:%f y:%f ", x, y);
}

void FreeCameraController::AttachTo(Camera* cam)
{
	if (cam == nullptr)
	{
		DEBUG_MESSAGE(RAY_ERROR, "the camera attached to is null!");
	}

	m_Camera = cam;
}

void FreeCameraController::Update(float deltaTime)
{
	Vector speed;
	if (m_bMoveFoward)
	{
		speed += m_Camera->GetFoward() * deltaTime;
	}
	else
	{
	}
}