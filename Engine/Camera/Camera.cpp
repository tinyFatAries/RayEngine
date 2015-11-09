#include "Camera.h"

Camera::Camera()
	: m_AspectRatio(1024.0f/768)
	, m_Near(10)
	, m_Far(1000)
	, m_FOV(60)
	, m_Position(Vector(0,0,0))
	, m_Target(Vector(0, 0, 1))
	, m_Direction(Vector(0, 0, 1))
	, m_PrjType(Perspective)
{

}

Camera::~Camera()
{

}

void Camera::Update()
{
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
	m_Target = pos;
	m_ViewMatrix = LookAtMatrix(m_Position, m_Target, Vector::UpVector);
}

void Camera::Project()
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









