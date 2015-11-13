#pragma once
#include "../Math/RayMath.h"

class CameraController;

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
	void Project(ProjectType type);

	const float GetFOV() const;
	const float GetNear() const;
	const float GetFar() const;
	const float GetRatio() const;

	void SetPosition(Vector& pos);
	void SetDirection(Vector& direct);
	void LookAt(Vector& pos);

	const Vector GetFoward();
	const Vector GetRight();
	const Vector GetUp();
	
	void SetView(Matrix& view);
	void SetProj(Matrix& proj);

	const Matrix GetView() const;
	const Matrix GetProj() const;
	const Matrix GetViewProj() const;

	void Update(float deltaTime);

	void Move(Vector& vec);
	void Pitch(const float angle);
	void Yaw(const float angle);
	void Roll(const float angle);
	void Rotate(const Vector& axis, const float angle);
	void Rotate(Quaternion& q);

	void SetYawFixed(bool yawFixed);
	void SetYawFixedVector(Vector& vec);

	void SetController(CameraController* camController);

	void InvalidateView();
private:
	Matrix m_ViewMatrix;
	Matrix m_ProjMatrix;

	float m_AspectRatio;
	float m_Near, m_Far, m_FOV;

	Vector m_Position;
	Vector m_Direction;
	Vector m_Right;
	Vector m_Up;

	Vector m_YawFixedVector;

	ProjectType m_PrjType;
	bool m_bYawFixed;

	bool m_bValideView;
	CameraController* m_Controller;

};