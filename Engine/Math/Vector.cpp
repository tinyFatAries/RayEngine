#include "Vector.h"

const Vector Vector::ZeroVector(0.0f, 0.0f, 0.0f);
const Vector Vector::UpVector(0.0f, 1.0f, 0.0f);
const Vector Vector::FowardVector(1.0f, 0.0f, 0.0f);

FORCEINLINE Vector operator*(float Scale, const Vector& V)
{
	return V.operator*(Scale);
}

FORCEINLINE Vector::Vector()
{}

FORCEINLINE Vector::Vector(float InF)
	: X(InF), Y(InF), Z(InF)
{}

FORCEINLINE Vector::Vector(float InX, float InY, float InZ)
	: X(InX), Y(InY), Z(InZ)
{}

FORCEINLINE Vector Vector::operator^(const Vector& V) const
{
	return Vector
		(
		Y * V.Z - Z * V.Y,
		Z * V.X - X * V.Z,
		X * V.Y - Y * V.X
		);
}

FORCEINLINE  Vector Vector::CrossProduct(const Vector& A, const Vector& B)
{
	return A ^ B;
}

FORCEINLINE float Vector::operator|(const Vector& V) const
{
	return X*V.X + Y*V.Y + Z*V.Z;
}

FORCEINLINE static float DotProduct(const Vector& A, const Vector& B)
{
	return A | B;
}

FORCEINLINE Vector Vector::operator+(const Vector& V) const
{
	return Vector(X + V.X, Y + V.Y, Z + V.Z);
}

FORCEINLINE Vector Vector::operator-(const Vector& V) const
{
	return Vector(X - V.X, Y - V.Y, Z - V.Z);
}

FORCEINLINE Vector Vector::operator+(float Bias) const
{
	return Vector(X + Bias, Y + Bias, Z + Bias);
}

FORCEINLINE Vector Vector::operator-(float Bias) const
{
	return Vector(X - Bias, Y - Bias, Z - Bias);
}

FORCEINLINE Vector Vector::operator*(float Scale) const
{
	return Vector(X * Scale, Y * Scale, Z * Scale);
}

FORCEINLINE Vector Vector::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return Vector(X * RScale, Y * RScale, Z * RScale);
}

FORCEINLINE Vector Vector::operator*(const Vector& V) const
{
	return Vector(X * V.X, Y * V.Y, Z * V.Z);
}

FORCEINLINE Vector Vector::operator/(const Vector& V) const
{
	return Vector(X / V.X, Y / V.Y, Z / V.Z);
}

FORCEINLINE bool Vector::operator==(const Vector& V) const
{
	return X == V.X && Y == V.Y && Z == V.Z;
}

FORCEINLINE bool Vector::operator!=(const Vector& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z;
}

FORCEINLINE bool Vector::Equals(const Vector& V, float Tolerance) const
{
	return Math::Abs(X - V.X) < Tolerance && Math::Abs(Y - V.Y) < Tolerance && Math::Abs(Z - V.Z) < Tolerance;
}

FORCEINLINE bool Vector::AllComponentsEqual(float Tolerance) const
{
	return Math::Abs(X - Y) < Tolerance && Math::Abs(Y - Z) < Tolerance && Math::Abs(Z - X) < Tolerance;
}

FORCEINLINE Vector Vector::operator-() const
{
	return Vector(-X, -Y, -Z);
}

FORCEINLINE Vector Vector::operator+=(const Vector& V)
{
	X += V.X; Y += V.Y; Z += V.Z;
	return *this;
}

FORCEINLINE Vector Vector::operator-=(const Vector& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z;
	return *this;
}

FORCEINLINE Vector Vector::operator*=(float Scale)
{
	X *= Scale; Y *= Scale; Z *= Scale;
	return *this;
}

FORCEINLINE Vector Vector::operator/=(float V)
{
	const float RV = 1.f / V;
	X *= RV; Y *= RV; Z *= RV;
	return *this;
}

FORCEINLINE Vector Vector::operator*=(const Vector& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z;
	return *this;
}

FORCEINLINE Vector Vector::operator/=(const Vector& V)
{
	X /= V.X; Y /= V.Y; Z /= V.Z;
	return *this;
}

FORCEINLINE float& Vector::operator[](int32 Index)
{
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else
	{
		return Z;
	}
}

FORCEINLINE float Vector::operator[](int32 Index)const
{
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else
	{
		return Z;
	}
}

FORCEINLINE float& Vector::Component(int32 Index)
{
	return (&X)[Index];
}

FORCEINLINE float Vector::Component(int32 Index) const
{
	return (&X)[Index];
}

FORCEINLINE void Vector::Set(float InX, float InY, float InZ)
{
	X = InX;
	Y = InY;
	Z = InZ;
}

float Vector::GetMax() const
{
	return fmaxf(fmaxf(X, Y), Z);
}

float Vector::GetAbsMax() const
{
	return fmaxf(fmaxf(Math::Abs(X), Math::Abs(Y)), Math::Abs(Z));
}

float Vector::GetMin() const
{
	return fminf(fminf(X, Y), Z);
}

float Vector::GetAbsMin() const
{
	return fminf(fminf(Math::Abs(X), Math::Abs(Y)), Math::Abs(Z));
}

Vector Vector::ComponentMin(const Vector& Other) const
{
	return Vector(fminf(X, Other.X), fminf(Y, Other.Y), fminf(Z, Other.Z));
}

Vector Vector::ComponentMax(const Vector& Other) const
{
	return Vector(fmaxf(X, Other.X), fmaxf(Y, Other.Y), fmaxf(Z, Other.Z));
}

Vector Vector::GetAbs() const
{
	return Vector(Math::Abs(X), Math::Abs(Y), Math::Abs(Z));
}

float Vector::Size() const
{
	return Math::Sqrt(X*X + Y*Y + Z*Z);
}

float Vector::SizeSquared() const
{
	return X*X + Y*Y + Z*Z;
}

float Vector::Size2D() const
{
	return Math::Sqrt(X*X + Y*Y);
}

float Vector::SizeSquared2D() const
{
	return X*X + Y*Y;
}

bool Vector::IsNearlyZero(float Tolerance) const
{
	return
		Math::Abs(X) < Tolerance
		&&	Math::Abs(Y) < Tolerance
		&&	Math::Abs(Z) < Tolerance;
}

bool Vector::IsZero() const
{
	return X == 0.f && Y == 0.f && Z == 0.f;
}

bool Vector::Normalize(float Tolerance)
{
	const float SquareSum = X*X + Y*Y + Z*Z;
	if (SquareSum > Tolerance)
	{
		const float Scale = Math::InvSqrt(SquareSum);
		X *= Scale; Y *= Scale; Z *= Scale;
		return true;
	}
	return false;
}

bool Vector::IsNormalized() const
{
	return Math::Abs(1.f - SizeSquared()) < THRESH_VECTOR_NORMALIZED;
}

Vector Vector::Reciprocal() const
{
	Vector RecVector;
	if (X != 0.f)
	{
		RecVector.X = 1.f / X;
	}
	else
	{
		RecVector.X = BIG_NUMBER;
	}
	if (Y != 0.f)
	{
		RecVector.Y = 1.f / Y;
	}
	else
	{
		RecVector.Y = BIG_NUMBER;
	}
	if (Z != 0.f)
	{
		RecVector.Z = 1.f / Z;
	}
	else
	{
		RecVector.Z = BIG_NUMBER;
	}

	return RecVector;
}


bool Vector::IsUniform(float Tolerance) const
{
	return (Math::Abs(X - Y) < Tolerance) && (Math::Abs(Y - Z) < Tolerance);
}


Vector Vector::MirrorByVector(const Vector& MirrorNormal) const
{
	return *this - MirrorNormal*(2.f * (*this | MirrorNormal));
}

//Vector Vector::MirrorByPlane(const Plane& Plane) const
//{
//
//}


FORCEINLINE Vector Vector::RotateAngleAxis(const float AngleDeg, const Vector& Axis) const
{
	const float S = sinf(AngleDeg * PI / 180.0f);
	const float C = cosf(AngleDeg * PI / 180.0f);

	const float XX = Axis.X * Axis.X;
	const float YY = Axis.Y * Axis.Y;
	const float ZZ = Axis.Z * Axis.Z;

	const float XY = Axis.X * Axis.Y;
	const float YZ = Axis.Y * Axis.Z;
	const float ZX = Axis.Z * Axis.X;

	const float XS = Axis.X * S;
	const float YS = Axis.Y * S;
	const float ZS = Axis.Z * S;

	const float OMC = 1.f - C;

	return Vector(
		(OMC * XX + C) * X + (OMC * XY - ZS) * Y + (OMC * ZX + YS) * Z,
		(OMC * XY + ZS) * X + (OMC * YY + C) * Y + (OMC * YZ - XS) * Z,
		(OMC * ZX - YS) * X + (OMC * YZ + XS) * Y + (OMC * ZZ + C) * Z
		);
}

Vector Vector::GetSafeNormal(float Tolerance) const
{
	const float SquareSum = X*X + Y*Y + Z*Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == 1.f)
	{
		return *this;
	}
	else if (SquareSum < Tolerance)
	{
		return Vector::ZeroVector;
	}

	const float Scale = Math::InvSqrt(SquareSum);

	return Vector(X*Scale, Y*Scale, Z*Scale);
}


Vector Vector::GetSafeNormal2D(float Tolerance) const
{
	const float SquareSum = X*X + Y*Y;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == 1.f)
	{
		if (Z == 0.f)
		{
			return *this;
		}
		else
		{
			return Vector(X, Y, 0.f);
		}
	}
	else if (SquareSum < Tolerance)
	{
		return Vector::ZeroVector;
	}


	const float Scale = Math::InvSqrt(SquareSum);

	return Vector(X*Scale, Y*Scale, 0.f);
}


FORCEINLINE Vector Vector::ProjectOnTo(const Vector& A) const
{
	return (A * ((*this | A) / (A | A))); //v * (u dot v)/(v dot v)
}


FORCEINLINE Vector Vector::ProjectOnToNormal(const Vector& Normal) const
{
	return (Normal * (*this | Normal));
}

//TODO: implement Math::isNaN first
bool Vector::ContainsNaN() const
{
	return true;
}

FORCEINLINE bool Vector::IsUnit(float LengthSquaredTolerance) const
{
	return Math::Abs(1.0 - SizeSquared()) < LengthSquaredTolerance;
}

std::string Vector::ToString() const
{
	char text[20];
	sprintf(text, "X=%3.3f Y=%3.3f Z=%3.3f", X, Y, Z);
	return std::string(text);
}

inline bool Vector::PointsAreSame(const Vector &P, const Vector &Q)
{
	float Temp;
	Temp = P.X - Q.X;
	if ((Temp > -THRESH_POINTS_ARE_SAME) && (Temp < THRESH_POINTS_ARE_SAME))
	{
		Temp = P.Y - Q.Y;
		if ((Temp > -THRESH_POINTS_ARE_SAME) && (Temp < THRESH_POINTS_ARE_SAME))
		{
			Temp = P.Z - Q.Z;
			if ((Temp > -THRESH_POINTS_ARE_SAME) && (Temp < THRESH_POINTS_ARE_SAME))
			{
				return true;
			}
		}
	}
	return false;
}


inline bool Vector::PointsAreNear(const Vector &Point1, const Vector &Point2, float Dist)
{
	float Temp;
	Temp = (Point1.X - Point2.X); if (Math::Abs(Temp) >= Dist) return false;
	Temp = (Point1.Y - Point2.Y); if (Math::Abs(Temp) >= Dist) return false;
	Temp = (Point1.Z - Point2.Z); if (Math::Abs(Temp) >= Dist) return false;
	return true;
}


inline float Vector::PointPlaneDist(const Vector &Point, const Vector &PlaneBase, const Vector &PlaneNormal)
{
	return (Point - PlaneBase) | PlaneNormal;
}

inline Vector Vector::PointPlaneProject(const Vector& Point, const Vector& PlaneBase, const Vector& PlaneNormal)
{
	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - Vector::PointPlaneDist(Point, PlaneBase, PlaneNormal) * PlaneNormal;
}

FORCEINLINE  float Vector::Dist(const Vector &V1, const Vector &V2)
{
	return Math::Sqrt((V2.X - V1.X)*(V2.X - V1.X) + (V2.Y - V1.Y)*(V2.Y - V1.Y) + (V2.Y - V1.Y)*(V2.Z - V1.Z));
}

FORCEINLINE float Vector::DistSquared(const Vector &V1, const Vector &V2)
{
	return (V2.X - V1.X)*(V2.X - V1.X) + (V2.Y - V1.Y)*(V2.Y - V1.Y) + (V2.Y - V1.Y)*(V2.Z - V1.Z);
}

void Vector::ToDirectionAndLength(Vector &OutDir, float &OutLength) const
{
	OutLength = Size();
	if (OutLength > SMALL_NUMBER)
	{
		float OneOverLength = 1.0f / OutLength;
		OutDir = Vector(X*OneOverLength, Y*OneOverLength, Z*OneOverLength);
	}
	else
	{
		OutDir = Vector::ZeroVector;
	}
}

//TODO::implement FloatSelect
FORCEINLINE Vector Vector::GetSignVector() const
{}

Vector Vector::Projection() const
{
	const float RZ = 1.f / Z;
	return Vector(X*RZ, Y*RZ, 1);
}

FORCEINLINE Vector Vector::GetUnsafeNormal() const
{
	const float Scale = Math::InvSqrt(X*X + Y*Y + Z*Z);

	return Vector(X*Scale, Y*Scale, Z*Scale);
}