//===========================================================================
// Vector: Base 3d vector.
//===========================================================================

#pragma once

#include <stdio.h>
#include <string>
#include "MathUtility.h"


/**
 * A vector in 3-D space composed of components (X, Y, Z) with floating point precision
 */
struct Vector
{
public:
	/** Vector's X component. */
	float X;

	/** Vector's Y component. */
	float Y;

	/** Vector's Z component. */
	float Z;

public:

	/* A zero vector (0,0,0) */
	static const Vector ZeroVector;

	/* World up vector (0,0,1) */
	static const Vector UpVector;

	/* Ray's forward vector (1, 0, 0) */
	static const Vector FowardVector;

public:
	/** Default constructor (no initialization). */
	FORCEINLINE Vector();

	/**
	* Constructor initializing all components to a single float value.
	*
	* @param InF Value to set all components to.
	*/
	explicit FORCEINLINE Vector(float InF);

	/**
	* Constructor using initial values for each component.
	*
	* @param InX X Coordinate.
	* @param InY Y Coordinate.
	* @param InZ Z Coordinate.
	*/
	FORCEINLINE Vector(float InX, float InY, float InZ);

public:
	/**
	* Calculate cross product between this and another vector.
	*
	* @param V The other vector.
	* @return The cross product.
	*/
	FORCEINLINE Vector operator^(const Vector& V) const;

	/**
	* Calculate the cross product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The cross product.
	*/
	FORCEINLINE static Vector CrossProduct(const Vector& A, const Vector& B);

	/**
	* Calculate the dot product between this and another vector.
	*
	* @param V The other vector.
	* @return The dot product.
	*/
	FORCEINLINE float operator|(const Vector& V) const;

	/**
	* Calculate the dot product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The dot product.
	*/
	FORCEINLINE static float DotProduct(const Vector& A, const Vector& B);

	/**
	* Gets the result of component-wise addition of this and another vector.
	*
	* @param V The vector to add to this.
	* @return The result of vector addition.
	*/
	FORCEINLINE Vector operator+(const Vector& V) const;

	/**
	* Gets the result of component-wise subtraction of this by another vector.
	*
	* @param V The vector to subtract from this.
	* @return The result of vector subtraction.
	*/
	FORCEINLINE Vector operator-(const Vector& V) const;

	/**
	* Gets the result of adding to each component of the vector.
	*
	* @param Bias How much to add to each component.
	* @return The result of addition.
	*/
	FORCEINLINE Vector operator+(float Bias) const;

	/**
	* Gets the result of subtracting from each component of the vector.
	*
	* @param Bias How much to subtract from each component.
	* @return The result of subtraction.
	*/
	FORCEINLINE Vector operator-(float Bias) const;

	/**
	* Gets the result of scaling the vector (multiplying each component by a value).
	*
	* @param Scale What to multiply each component by.
	* @return The result of multiplication.
	*/
	FORCEINLINE Vector operator*(float Scale) const;

	/**
	* Gets the result of dividing each component of the vector by a value.
	*
	* @param Scale What to divide each component by.
	* @return The result of division.
	*/
	FORCEINLINE Vector operator/(float Scale) const;

	/**
	* Gets the result of component-wise multiplication of this vector by another.
	*
	* @param V The vector to multiply with.
	* @return The result of multiplication.
	*/
	FORCEINLINE Vector operator*(const Vector& V) const;

	/**
	* Gets the result of component-wise division of this vector by another.
	*
	* @param V The vector to divide by.
	* @return The result of division.
	*/
	FORCEINLINE Vector operator/(const Vector& V) const;

	// Binary comparison operators.
	/**
	* Check against another vector for equality.
	*
	* @param V The vector to check against.
	* @return true if the vectors are equal, false otherwise.
	*/
	bool operator==(const Vector& V) const;

	/**
	* Check against another vector for inequality.
	*
	* @param V The vector to check against.
	* @return true if the vectors are not equal, false otherwise.
	*/
	bool operator!=(const Vector& V) const;

	/**
	* Check against another vector for equality, within specified error limits.
	*
	* @param V The vector to check against.
	* @param Tolerance Error tolerance.
	* @return true if the vectors are equal within tolerance limits, false otherwise.
	*/
	bool Equals(const Vector& V, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Checks whether all components of this vector are the same, within a tolerance.
	*
	* @param Tolerance Error tolerance.
	* @return true if the vectors are equal within tolerance limits, false otherwise.
	*/
	bool AllComponentsEqual(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Get a negated copy of the vector.
	*
	* @return A negated copy of the vector.
	*/
	FORCEINLINE Vector operator-() const;

	/**
	* Adds another vector to this.
	* Uses component-wise addition.
	*
	* @param V Vector to add to this.
	* @return Copy of the vector after addition.
	*/
	FORCEINLINE Vector operator+=(const Vector& V);

	/**
	* Subtracts another vector from this.
	* Uses component-wise subtraction.
	*
	* @param V Vector to subtract from this.
	* @return Copy of the vector after subtraction.
	*/
	FORCEINLINE Vector operator-=(const Vector& V);

	/**
	* Scales the vector.
	*
	* @param Scale Amount to scale this vector by.
	* @return Copy of the vector after scaling.
	*/
	FORCEINLINE Vector operator*=(float Scale);

	/**
	* Divides the vector by a number.
	*
	* @param V What to divide this vector by.
	* @return Copy of the vector after division.
	*/
	Vector operator/=(float V);

	/**
	* Multiplies the vector with another vector, using component-wise multiplication.
	*
	* @param V What to multiply this vector with.
	* @return Copy of the vector after multiplication.
	*/
	Vector operator*=(const Vector& V);

	/**
	* Divides the vector by another vector, using component-wise division.
	*
	* @param V What to divide vector by.
	* @return Copy of the vector after division.
	*/
	Vector operator/=(const Vector& V);

	/**
	* Gets specific component of the vector.
	*
	* @param Index the index of vector component
	* @return reference to component.
	*/
	float& operator[](int32 Index);

	/**
	* Gets specific component of the vector.
	*
	* @param Index the index of vector component
	* @return Copy of the component.
	*/
	float operator[](int32 Index)const;

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	*
	* @return Reference to the specified component.
	*/
	float& Component(int32 Index);

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	* @return Copy of the specified component.
	*/
	float Component(int32 Index) const;

	// Simple functions.

	/**
	* Set the values of the vector directly.
	*
	* @param InX New X coordinate.
	* @param InY New Y coordinate.
	* @param InZ New Z coordinate.
	*/
	void Set(float InX, float InY, float InZ);

	/**
	* Get the maximum value of the vector's components.
	*
	* @return The maximum value of the vector's components.
	*/
	float GetMax() const;

	/**
	* Get the maximum absolute value of the vector's components.
	*
	* @return The maximum absolute value of the vector's components.
	*/
	float GetAbsMax() const;

	/**
	* Get the minimum value of the vector's components.
	*
	* @return The minimum value of the vector's components.
	*/
	float GetMin() const;

	/**
	* Get the minimum absolute value of the vector's components.
	*
	* @return The minimum absolute value of the vector's components.
	*/
	float GetAbsMin() const;

	/** Gets the component-wise min of two vectors. */
	Vector ComponentMin(const Vector& Other) const;

	/** Gets the component-wise max of two vectors. */
	Vector ComponentMax(const Vector& Other) const;

	/**
	* Get a copy of this vector with absolute value of each component.
	*
	* @return A copy of this vector with absolute value of each component.
	*/
	Vector GetAbs() const;

	/**
	* Get the length (magnitude) of this vector.
	*
	* @return The length of this vector.
	*/
	float Size() const;

	/**
	* Get the squared length of this vector.
	*
	* @return The squared length of this vector.
	*/
	float SizeSquared() const;

	/**
	* Get the length of the 2D components of this vector.
	*
	* @return The 2D length of this vector.
	*/
	float Size2D() const;

	/**
	* Get the squared length of the 2D components of this vector.
	*
	* @return The squared 2D length of this vector.
	*/
	float SizeSquared2D() const;

	/**
	* Checks whether vector is near to zero within a specified tolerance.
	*
	* @param Tolerance Error tolerance.
	* @return true if the vector is near to zero, false otherwise.
	*/
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Checks whether all components of the vector are exactly zero.
	*
	* @return true if the vector is exactly zero, false otherwise.
	*/
	bool IsZero() const;

	/**
	* Normalize this vector in-place if it is large enough, set it to (0,0,0) otherwise.
	*
	* @param Tolerance Minimum squared length of vector for normalization.
	* @return true if the vector was normalized correctly, false otherwise.
	*/
	bool Normalize(float Tolerance = SMALL_NUMBER);

	/**
	* Checks whether vector is normalized.
	*
	* @return true if Normalized, false otherwise.
	*/
	bool IsNormalized() const;

	/**
	* Util to convert this vector into a unit direction vector and its original length.
	*
	* @param OutDir Reference passed in to store unit direction vector.
	* @param OutLength Reference passed in to store length of the vector.
	*/
	void ToDirectionAndLength(Vector &OutDir, float &OutLength) const;

	/**
	* Get a copy of the vector as sign only.
	* Each component is set to +1 or -1, with the sign of zero treated as +1.
	*
	* @param A copy of the vector with each component set to +1 or -1
	*/
	FORCEINLINE Vector GetSignVector() const;

	/**
	* Projects 2D components of vector based on Z.
	*
	* @return Projected version of vector based on Z.
	*/
	Vector Projection() const;

	/**
	* Calculates normalized version of vector without checking for zero length.
	*
	* @return Normalized version of vector.
	* @see GetSafeNormal()
	*/
	FORCEINLINE Vector GetUnsafeNormal() const;

	/**
	* Gets the reciprocal of this vector, avoiding division by zero.
	* Zero components are set to BIG_NUMBER.
	*
	* @return Reciprocal of this vector.
	*/
	Vector Reciprocal() const;

	/**
	* Check whether X, Y and Z are nearly equal.
	*
	* @param Tolerance Specified Tolerance.
	* @return true if X == Y == Z within the specified tolerance.
	*/
	bool IsUniform(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Mirror a vector about a normal vector.
	*
	* @param MirrorNormal Normal vector to mirror about.
	* @return Mirrored vector.
	*/
	Vector MirrorByVector(const Vector& MirrorNormal) const;

	/**
	* Mirrors a vector about a plane.
	*
	* @param Plane Plane to mirror about.
	* @return Mirrored vector.
	*/
	//Vector MirrorByPlane(const Plane& Plane) const;

	/**
	* Rotates around Axis (assumes Axis.Size() == 1).
	*
	* @param Angle Angle to rotate (in degrees).
	* @param Axis Axis to rotate around.
	* @return Rotated Vector.
	*/
	Vector RotateAngleAxis(const float AngleDeg, const Vector& Axis) const;

	/**
	* Gets a normalized copy of the vector, checking it is safe to do so based on the length.
	* Returns zero vector if vector length is too small to safely normalize.
	*
	* @param Tolerance Minimum squared vector length.
	* @return A normalized copy if safe, (0,0,0) otherwise.
	*/
	Vector GetSafeNormal(float Tolerance = SMALL_NUMBER) const;

	/**
	* Gets a normalized copy of the 2D components of the vector, checking it is safe to do so. Z is set to zero.
	* Returns zero vector if vector length is too small to normalize.
	*
	* @param Tolerance Minimum squared vector length.
	* @return Normalized copy if safe, otherwise returns zero vector.
	*/
	Vector GetSafeNormal2D(float Tolerance = SMALL_NUMBER) const;

	/**
	* Gets a copy of this vector projected onto the input vector.
	*
	* @param A	Vector to project onto, does not assume it is normalized.
	* @return Projected vector.
	*/
	FORCEINLINE Vector ProjectOnTo(const Vector& A) const;

	/**
	* Gets a copy of this vector projected onto the input vector, which is assumed to be unit length.
	*
	* @param  Normal Vector to project onto (assumed to be unit length).
	* @return Projected vector.
	*/
	FORCEINLINE Vector ProjectOnToNormal(const Vector& Normal) const;

	/**
	* Return the FRotator corresponding to the direction that the vector
	* is pointing in.  Sets Yaw and Pitch to the proper numbers, and sets
	* roll to zero because the roll can't be determined from a vector.
	*
	* @return The FRotator from the vector's direction.
	*/
	//Rotator Rotation() const;

	/**
	* Utility to check if there are any NaNs in this vector.
	*
	* @return true if there are any NaNs in this vector, false otherwise.
	*/
	bool ContainsNaN() const;

	/**
	* Check if the vector is of unit length, with specified tolerance.
	*
	* @param LengthSquaredTolerance Tolerance against squared length.
	* @return true if the vector is a unit vector within the specified tolerance.
	*/
	FORCEINLINE bool IsUnit(float LengthSquaredTolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Get a textual representation of this vector.
	*
	* @return A string describing the vector.
	*/
	std::string ToString() const;

	/**
	* Compare two points and see if they're the same, using a threshold.
	*
	* @param P First vector.
	* @param Q Second vector.
	* @return Whether points are the same within a threshold. Uses fast distance approximation (linear per-component distance).
	*/
	static bool PointsAreSame(const Vector &P, const Vector &Q);

	/**
	* Compare two points and see if they're within specified distance.
	*
	* @param Point1 First vector.
	* @param Point2 Second vector.
	* @param Dist Specified distance.
	* @return Whether two points are within the specified distance. Uses fast distance approximation (linear per-component distance).
	*/
	static bool PointsAreNear(const Vector &Point1, const Vector &Point2, float Dist);

	/**
	* Calculate the signed distance (in the direction of the normal) between a point and a plane.
	*
	* @param Point The Point we are checking.
	* @param PlaneBase The Base Point in the plane.
	* @param PlaneNormal The Normal of the plane (assumed to be unit length).
	* @return Signed distance between point and plane.
	*/
	static float PointPlaneDist(const Vector &Point, const Vector &PlaneBase, const Vector &PlaneNormal);

	/**
	* Calculate the projection of a point on the given plane.
	*
	* @param Point The point to project onto the plane
	* @param Plane The plane
	* @return Projection of Point onto Plane
	*/
	//static Vector PointPlaneProject(const Vector& Point, const Plane& Plane);

	/**
	* Calculate the projection of a point on the plane defined by counter-clockwise (CCW) points A,B,C.
	*
	* @param Point The point to project onto the plane
	* @param A 1st of three points in CCW order defining the plane
	* @param B 2nd of three points in CCW order defining the plane
	* @param C 3rd of three points in CCW order defining the plane
	* @return Projection of Point onto plane ABC
	*/
	static Vector PointPlaneProject(const Vector& Point, const Vector& A, const Vector& B, const Vector& C);

	/**
	* Calculate the projection of a point on the plane defined by PlaneBase and PlaneNormal.
	*
	* @param Point The point to project onto the plane
	* @param PlaneBase Point on the plane
	* @param PlaneNorm Normal of the plane (assumed to be unit length).
	* @return Projection of Point onto plane
	*/
	static Vector PointPlaneProject(const Vector& Point, const Vector& PlaneBase, const Vector& PlaneNormal);

	/**
	* Euclidean distance between two points.
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The distance between two points.
	*/
	static FORCEINLINE float Dist(const Vector &V1, const Vector &V2);

	/**
	* Squared distance between two points.
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The squared distance between two points.
	*/
	static FORCEINLINE float DistSquared(const Vector &V1, const Vector &V2);
};

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