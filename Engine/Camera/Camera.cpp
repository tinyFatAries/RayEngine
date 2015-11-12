#include "Camera.h"
#include "CameraController.h"

Camera::Camera()
	: m_AspectRatio(1024.0f/768)
	, m_Near(10)
	, m_Far(1000)
	, m_FOV(60)
	, m_Position(Vector(0,0,0))
	, m_Direction(Vector(0, 0, 1))
	, m_Right(Vector(-1, 0, 0))
	, m_Up(Vector(0, 1, 0))
	, m_YawFixedVector(Vector::UpVector)
	, m_PrjType(Perspective)
	, m_bYawFixed(true)
	, m_Controller(nullptr)
{

}

Camera::~Camera()
{
	R_DELETE(m_Controller);
}

void Camera::Update(float deltaTime)
{
	if (m_Controller != nullptr)
	{
		m_Controller->Update(deltaTime);
	}
	const Vector ZAxis = (-m_Direction).GetSafeNormal();
	const Vector XAxis = (Vector::UpVector^ZAxis).GetSafeNormal();
	const Vector YAxis = ZAxis^XAxis;
	m_Direction.Normalize();
	m_Right = XAxis;
	m_Up = YAxis;

	for (uint16 rowIndex = 0; rowIndex < 3; ++rowIndex)
	{
		m_ViewMatrix.M[rowIndex][0] = (&XAxis.X)[rowIndex];
		m_ViewMatrix.M[rowIndex][1] = (&YAxis.X)[rowIndex];
		m_ViewMatrix.M[rowIndex][2] = (&ZAxis.X)[rowIndex];
		m_ViewMatrix.M[rowIndex][3] = 0.0f;
	}

	m_ViewMatrix.M[3][0] = -m_Position | XAxis;
	m_ViewMatrix.M[3][1] = -m_Position | YAxis;
	m_ViewMatrix.M[3][2] = -m_Position | ZAxis;
	m_ViewMatrix.M[3][3] = 1.0f;
}

void Camera::SetPosition(Vector& pos)
{
	m_Position = pos;
}

void Camera::SetDirection(Vector& direct)
{
	m_Direction = direct;
}

void Camera::SetRatio(float ratio)
{
	m_AspectRatio = ratio;
}

void Camera::SetFOV(float fov)
{
	m_FOV = fov;
}

void Camera::SetNearPlane(float near)
{
	m_Near = near;
}

void Camera::SetFarPlane(float far)
{
	m_Far = far;
}

void Camera::SetProjParameters(float ratio, float fov, float near, float far)
{
	m_AspectRatio = ratio;
	m_FOV = fov;
	m_Near = near;
	m_Far = far;
}

const float Camera::GetFar() const
{
	return m_Far;
}

const float Camera::GetNear() const
{
	return m_Near;
}

const float Camera::GetFOV() const
{
	return m_FOV;
}

const float Camera::GetRatio() const
{
	return m_AspectRatio;
}

const Matrix Camera::GetView() const
{
	return m_ViewMatrix;
}

const Matrix Camera::GetProj() const
{
	return m_ProjMatrix;
}

const Matrix Camera::GetViewProj() const
{
	return m_ViewMatrix * m_ProjMatrix;
}

void Camera::LookAt(Vector& pos)
{
	m_ViewMatrix = LookAtMatrix(m_Position, pos, Vector::UpVector);
}

void Camera::Project(ProjectType type)
{
	// Perspective projection
	if (m_PrjType == Perspective)
	{
		m_ProjMatrix = PerspectiveProjectMatrix(m_AspectRatio, m_FOV, m_Near, m_Far);
	}
	// Orthogonal projection
	else
	{
		//TODO:
		;
	}
}

const Vector Camera::GetFoward()
{
	return m_Direction;
}

const Vector Camera::GetRight()
{
	return m_Right;
}

const Vector Camera::GetUp()
{
	return m_Up;
}

void Camera::Move(Vector& vec)
{
	m_Position += vec;
	Update();
}

void Camera::Pitch(const float angle)
{
	Rotate(m_Right, angle);
}

void Camera::Yaw(const float angle)
{
	Vector yawAxis;
	if (m_bYawFixed)
	{
		yawAxis = m_YawFixedVector;
	}
	else
	{
		yawAxis = m_Up;
	}
	Rotate(yawAxis, angle);
}

void Camera::Roll(const float angle)
{
	Rotate(m_Direction, angle);
}

void Camera::Rotate(const Vector& axis, const float angle)
{
	Quaternion q(axis, angle);
	Rotate(q);
}

void Camera::Rotate(Quaternion& q)
{
	m_Direction = q.RotateVector(m_Direction);
	Update();
}

void Camera::SetYawFixed(bool yawFixed)
{
	m_bYawFixed = yawFixed;
}

void Camera::SetYawFixedVector(Vector& vec)
{
	m_YawFixedVector = vec;
}

void Camera::SetController(CameraController* camController)
{
	if (camController == nullptr)
	{
		DEBUG_MESSAGE(RAY_ERROR, "the camera controller is null!");
		return;
	}

	if (m_Controller != nullptr)
	{
		DEBUG_MESSAGE(RAY_EXCEPTION, "Attention! Camera should only have one controller, the old one was removed!!");
		R_DELETE(m_Controller);
	}

	m_Controller = camController;
	m_Controller->AttachTo(this);
}