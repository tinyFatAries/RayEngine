#pragma once
#include "../Math/RayMath.h"

enum ProjectType
{
	Perspective,
	Orthogonal
};

class Camera
{
public:
	Camera();
	~Camera();

	void SetRatio(float ratio);
	void SetFOV(float fov);
	void SetFarPlane(float far);
	void SetNearPlane(float near);
	void SetProjParameters(float ratio, float fov, float near, float far);
	void Project();

	const float GetFOV() const;
	const float GetNear() const;
	const float GetFar() const;
	const float GetRatio() const;

	const Matrix GetView() const;
	const Matrix GetProj() const;
	const Matrix GetViewProj() const;

	void SetView(Matrix& view);
	void SetProj(Matrix& proj);

	void Update();

	void SetPosition(Vector& pos);
	void SetDirection(Vector& direct);
	void LookAt(Vector& pos);
	
private:
	Matrix m_ViewMatrix;
	Matrix m_ProjMatrix;

	float m_AspectRatio;
	float m_Near, m_Far, m_FOV;

	Vector m_Position;
	Vector m_Target;
	Vector m_Direction;

	ProjectType m_PrjType;
};