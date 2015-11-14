#include "FreeCameraController.h"
#include "../Tools/RayUtils.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

FreeCameraController::FreeCameraController()
	: m_bMoveFoward(false)
	, m_bMoveBack(false)
	, m_bMoveLeft(false)
	, m_bMoveRight(false)
	, m_bMoveUp(false)
	, m_bMoveDown(false)
	, m_bFastMove(false)
	, m_Velocity(Vector::ZeroVector)
	, m_AccSpeed(0.5f)
	, m_MaxSpeed(0.5f)
	, m_bMouseMove(false)
{
	InputManager::getInstancePtr()->AddListener(this);
	m_CurPos = { -1.0f, -1.0f };
	m_LastPos= { -1.0f, -1.0f };
}

FreeCameraController::~FreeCameraController()
{
	InputManager::getInstancePtr()->RemoveListener(this);
}

void FreeCameraController::HandleKeyPress(int key, int scancode, int action, int mods)
{
	//DEBUG_MESSAGE(RAY_MESSAGE, "key pressed key:%d scancode:%d action:%d mods:%d", key, scancode, action, mods);
	switch (key)
	{
	case GLFW_KEY_W:
		m_bMoveFoward = (action == !GLFW_PRESS) ? false : true;
		break;
	case GLFW_KEY_A:
		m_bMoveLeft = (action == !GLFW_PRESS) ? false : true;
		break;
	case GLFW_KEY_S:
		m_bMoveBack = (action == !GLFW_PRESS) ? false : true;
		break;
	case GLFW_KEY_D:
		m_bMoveRight = (action == !GLFW_PRESS) ? false : true;
		break;
	case GLFW_KEY_PAGE_UP:
		m_bMoveUp = (action == !GLFW_PRESS) ? false : true;
		break;
	case GLFW_KEY_PAGE_DOWN:
		m_bMoveDown = (action == !GLFW_PRESS) ? false : true;
		break;
	case GLFW_KEY_LEFT_SHIFT:
		m_bFastMove = (action == !GLFW_PRESS) ? false : true;
		break;
	default:
		break;
	}
}

void FreeCameraController::HandleMouseClick(int button, int action, int mode)
{
	//DEBUG_MESSAGE(RAY_MESSAGE, "mouse clicked button:%d action:%d mods:%d", button, action, mode);
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_RIGHT:
		m_bMouseMove = (action == GLFW_RELEASE) ? false : true;
		break;
	default:
		break;
	}
}

void FreeCameraController::HandleMouseMove(double x, double y)
{
	//DEBUG_MESSAGE(RAY_MESSAGE, "mouse move x:%f y:%f ", x, y);
    m_CurPos.x = static_cast<float>(x);
    m_CurPos.y = static_cast<float>(y);
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
    /** 
	 * CameraController handle movement
     */
	Vector accel = Vector::ZeroVector;
	if (m_bMoveFoward) accel += m_Camera->GetFoward();
    if (m_bMoveBack) accel -= m_Camera->GetFoward();
    if (m_bMoveRight) accel += m_Camera->GetRight();
    if (m_bMoveLeft) accel -= m_Camera->GetRight();
    if (m_bMoveUp) accel += m_Camera->GetUp();
    if (m_bMoveDown) accel -= m_Camera->GetUp();

    float topSpeed = m_bFastMove ? m_MaxSpeed * 3 : m_MaxSpeed;
    if (accel.SizeSquared() != 0.0f)
    {
		accel.Normalize();
        m_Velocity+= (accel * m_AccSpeed * deltaTime);
    }
    else m_Velocity-= m_Velocity * deltaTime * 10;

    if (m_Velocity.SizeSquared() > topSpeed*topSpeed)
    {
        m_Velocity.Normalize();
        m_Velocity *= topSpeed;
    }
    else if (m_Velocity.SizeSquared() < 1e-06)
    {
        m_Velocity = Vector::ZeroVector;
    }

    Vector vec = m_Velocity;
    if(m_Velocity != Vector::ZeroVector) 
	{
		m_Camera->Move(vec); 
	}

	/**
	 * CameraController handle rotations
	 */
    if (m_bMouseMove)
    {
        if (m_LastPos.x != -1.0f && m_LastPos.y != -1.0f)
        {
            float xMove = m_CurPos.x - m_LastPos.x;
            float yMove = m_CurPos.y - m_LastPos.y;
            m_Camera->Yaw(-xMove*0.25f/180);
            m_Camera->Pitch(-yMove*0.25f/180);
        }
        m_LastPos = m_CurPos;
    }
	else
	{
		m_LastPos = m_CurPos;
	}
}