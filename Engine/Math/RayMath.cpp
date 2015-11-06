#include "RayMath.h"

//some static vriables
const Vector Vector::ZeroVector(0.0f, 0.0f, 0.0f);
const Vector Vector::UpVector(0.0f, 1.0f, 0.0f);
const Vector Vector::FowardVector(1.0f, 0.0f, 0.0f);

const Matrix Matrix::Identity(Vector(1.0f, 0.0f, 0.0f),
							  Vector(0.0f, 1.0f, 0.0f),
							  Vector(0.0f, 0.0f, 1.0f),
							  Vector(0.0f, 0.0f, 0.0f));

const Rotator Rotator::ZeroRotator(0, 0, 0);

const Quaternion Quaternion::Identity(0, 0, 0, 1);