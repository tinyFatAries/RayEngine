#pragma once

#include "CameraController.h"
#include "../Math/RayMath.h"

struct MouseCoord
{
	float x;
	float y;
};

class FreeCameraController : public CameraController 
{
public:
	FreeCameraController();
	~FreeCameraController();

	virtual void HandleKeyPress(int key, int scancode, int action, int mods);
	virtual void HandleMouseClick(int button, int action, int mode);
	virtual void HandleMouseMove(double x, double y);
	virtual void AttachTo(Camera* cam);
	virtual void Update(float deltaTime);

private:
	//Movement controll
	bool m_bMoveFoward;
	bool m_bMoveBack;
	bool m_bMoveLeft;
	bool m_bMoveRight;
	bool m_bMoveUp;
	bool m_bMoveDown;
	bool m_bFastMove;

	Vector m_Velocity;
	float m_AccSpeed;
	float m_MaxSpeed;

	//Rotation controll
	bool m_bMouseMove;
	MouseCoord m_CurPos, m_LastPos;
};