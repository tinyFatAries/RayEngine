//===========================================================================
// Vector4: 
//===========================================================================

#pragma once
#include "Vector.h"
#include "../Config/RayConifg.h"
#include "../Config/WindowPlatform.h"
/**
* A 4D homogeneous vector, 4x1 FLOATs, 16-byte aligned.
*/
struct Vector4
{
public:

	/** Holds the vector's X-component. */
	float X;

	/** Holds the vector's Y-component. */
	float Y;

	/** Holds the vector's Z-component. */
	float Z;

	/** Holds the vector's W-component. */
	float W;

public:
	/**
	* Constructor.
	*
	* @param InVector 3D Vector to set first three components.
	* @param InW W Coordinate.
	*/
	Vector4(const Vector& InVector, float InW = 1.0f);

	/**
	* Creates and initializes a new vector from the specified components.
	*
	* @param InX X Coordinate.
	* @param InY Y Coordinate.
	* @param InZ Z Coordinate.
	* @param InW W Coordinate.
	*/
	Vector4(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f, float InW = 1.0f);

public:

	/**
	* Access a specific component of the vector.
	*
	* @param ComponentIndex The index of the component.
	* @return Reference to the desired component.
	*/
	FORCEINLINE float& operator[](int32 ComponentIndex);

	/**
	* Access a specific component of the vector.
	*
	* @param ComponentIndex The index of the component.
	* @return Copy of the desired component.
	*/
	FORCEINLINE float operator[](int32 ComponentIndex) const;

	// Unary operators.

	/**
	* Gets a negated copy of the vector.
	*
	* @return A negated copy of the vector.
	*/
	FORCEINLINE Vector4 operator-() const;

	/**
	* Gets the result of adding a vector to this.
	*
	* @param V The vector to add.
	* @return The result of vector addition.
	*/
	FORCEINLINE Vector4 operator+(const Vector4& V) const;

	/**
	* Adds another vector to this one.
	*
	* @param V The other vector to add.
	* @return Copy of the vector after addition.
	*/
	FORCEINLINE Vector4 operator+=(const Vector4& V);

	/**
	* Gets the result of subtracting a vector from this.
	*
	* @param V The vector to subtract.
	* @return The result of vector subtraction.
	*/
	FORCEINLINE Vector4 operator-(const Vector4& V) const;

	/**
	* Gets the result of scaling this vector.
	*
	* @param Scale The scaling factor.
	* @return The result of vector scaling.
	*/
	FORCEINLINE Vector4 operator*(float Scale) const;

	/**
	* Gets the result of dividing this vector.
	*
	* @param Scale What to divide by.
	* @return The result of division.
	*/
	Vector4 operator/(float Scale) const;

	/**
	* Gets the result of dividing this vector.
	*
	* @param V What to divide by.
	* @return The result of division.
	*/
	Vector4 operator/(const Vector4& V) const;

	/**
	* Gets the result of multiplying a vector with this.
	*
	* @param V The vector to multiply.
	* @return The result of vector multiplication.
	*/
	Vector4 operator*(const Vector4& V) const;

	/**
	* Gets the result of multiplying a vector with another Vector (component wise).
	*
	* @param V The vector to multiply.
	* @return The result of vector multiplication.
	*/
	Vector4 operator*=(const Vector4& V);

	/**
	* Gets the result of dividing a vector with another Vector (component wise).
	*
	* @param V The vector to divide with.
	* @return The result of vector multiplication.
	*/
	Vector4 operator/=(const Vector4& V);

	/**
	* Gets the result of scaling this vector.
	*
	* @param Scale The scaling factor.
	* @return The result of vector scaling.
	*/
	Vector4 operator*=(float S);

	/**
	* Calculates 3D Dot product of two 4D vectors.
	*
	* @param V1 The first vector.
	* @param V2 The second vector.
	* @return The 3D Dot product.
	*/
	friend FORCEINLINE float Dot3(const Vector4& V1, const Vector4& V2)
	{
		return V1.X*V2.X + V1.Y*V2.Y + V1.Z*V2.Z;
	}

	/**
	* Calculates 4D Dot product.
	*
	* @param V1 The first vector.
	* @param V2 The second vector.
	* @return The 4D Dot Product.
	*/
	friend FORCEINLINE float Dot4(const Vector4& V1, const Vector4& V2)
	{
		return V1.X*V2.X + V1.Y*V2.Y + V1.Z*V2.Z + V1.W*V2.W;
	}

	/**
	* Scales a vector.
	*
	* @param Scale The scaling factor.
	* @param V The vector to scale.
	* @return The result of scaling.
	*/
	friend FORCEINLINE Vector4 operator*(float Scale, const Vector4& V)
	{
		return V.operator*(Scale);
	}

	/**
	* Checks for equality against another vector.
	*
	* @param V The other vector.
	* @return true if the two vectors are the same, otherwise false.
	*/
	bool operator==(const Vector4& V) const;

	/**
	* Checks for inequality against another vector.
	*
	* @param V The other vector.
	* @return true if the two vectors are different, otherwise false.
	*/
	bool operator!=(const Vector4& V) const;

	/**
	* Calculate Cross product between this and another vector.
	*
	* @param V The other vector.
	* @return The Cross product.
	*/
	Vector4 operator^(const Vector4& V) const;

public:

	// Simple functions.

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component.
	* @return Reference to the component.
	*/
	float& Component(int32 Index);

	/**
	* Error tolerant comparison.
	*
	* @param V Vector to compare against.
	* @param Tolerance Error Tolerance.
	* @return true if the two vectors are equal within specified tolerance, otherwise false.
	*/
	bool Equals(const Vector4& V, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Check if the vector is of unit length, with specified tolerance.
	*
	* @param LengthSquaredTolerance Tolerance against squared length.
	* @return true if the vector is a unit vector within the specified tolerance.
	*/
	bool IsUnit3(float LengthSquaredTolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Returns a normalized copy of the vector if safe to normalize.
	*
	* @param Tolerance Minimum squared length of vector for normalization.
	* @return A normalized copy of the vector or a zero vector.
	*/
	FORCEINLINE Vector4 GetSafeNormal(float Tolerance = SMALL_NUMBER) const;

	/**
	* Calculates normalized version of vector without checking if it is non-zero.
	*
	* @return Normalized version of vector.
	*/
	FORCEINLINE Vector4 GetUnsafeNormal3() const;

	/**
	* Set all of the vectors coordinates.
	*
	* @param InX New X Coordinate.
	* @param InY New Y Coordinate.
	* @param InZ New Z Coordinate.
	* @param InW New W Coordinate.
	*/
	FORCEINLINE void Set(float InX, float InY, float InZ, float InW);

	/**
	* Get the length of this vector not taking W component into account.
	*
	* @return The length of this vector.
	*/
	float Size3() const;

	/**
	* Get the squared length of this vector not taking W component into account.
	*
	* @return The squared length of this vector.
	*/
	float SizeSquared3() const;

	/** Utility to check if there are any NaNs in this vector. */
	bool ContainsNaN() const;

	/** Utility to check if all of the components of this vector are nearly zero given the tolerance. */
	bool IsNearlyZero3(float Tolerance = KINDA_SMALL_NUMBER) const;

	/** Reflect vector. */
	Vector4 Reflect3(const Vector4& Normal) const;
};


/* Vector4 inline functions
*****************************************************************************/

FORCEINLINE Vector4::Vector4(const Vector& InVector, float InW)
	: X(InVector.X)
	, Y(InVector.Y)
	, Z(InVector.Z)
	, W(InW)
{
}


FORCEINLINE Vector4::Vector4(float InX, float InY, float InZ, float InW)
	: X(InX)
	, Y(InY)
	, Z(InZ)
	, W(InW)
{
}


FORCEINLINE float& Vector4::operator[](int32 ComponentIndex)
{
	return (&X)[ComponentIndex];
}


FORCEINLINE float Vector4::operator[](int32 ComponentIndex) const
{
	return (&X)[ComponentIndex];
}


FORCEINLINE void Vector4::Set(float InX, float InY, float InZ, float InW)
{
	X = InX;
	Y = InY;
	Z = InZ;
	W = InW;
}


FORCEINLINE Vector4 Vector4::operator-() const
{
	return Vector4(-X, -Y, -Z, -W);
}


FORCEINLINE Vector4 Vector4::operator+(const Vector4& V) const
{
	return Vector4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}


FORCEINLINE Vector4 Vector4::operator+=(const Vector4& V)
{
	X += V.X; Y += V.Y; Z += V.Z; W += V.W;
	return *this;
}


FORCEINLINE Vector4 Vector4::operator-(const Vector4& V) const
{
	return Vector4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}


FORCEINLINE Vector4 Vector4::operator*(float Scale) const
{
	return Vector4(X * Scale, Y * Scale, Z * Scale, W * Scale);
}


FORCEINLINE Vector4 Vector4::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return Vector4(X * RScale, Y * RScale, Z * RScale, W * RScale);
}


FORCEINLINE Vector4 Vector4::operator*(const Vector4& V) const
{
	return Vector4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
}


FORCEINLINE Vector4 Vector4::operator^(const Vector4& V) const
{
	return Vector4(
		Y * V.Z - Z * V.Y,
		Z * V.X - X * V.Z,
		X * V.Y - Y * V.X,
		0.0f
		);
}


FORCEINLINE float& Vector4::Component(int32 Index)
{
	return (&X)[Index];
}


FORCEINLINE bool Vector4::operator==(const Vector4& V) const
{
	return ((X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W));
}


FORCEINLINE bool Vector4::operator!=(const Vector4& V) const
{
	return ((X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W));
}


FORCEINLINE bool Vector4::Equals(const Vector4& V, float Tolerance) const
{
	return Math::Abs(X - V.X) < Tolerance && Math::Abs(Y - V.Y) < Tolerance && Math::Abs(Z - V.Z) < Tolerance && Math::Abs(W - V.W) < Tolerance;
}


FORCEINLINE Vector4 Vector4::GetSafeNormal(float Tolerance) const
{
	const float SquareSum = X*X + Y*Y + Z*Z;
	if (SquareSum > Tolerance)
	{
		const float Scale = Math::InvSqrt(SquareSum);
		return Vector4(X*Scale, Y*Scale, Z*Scale, 0.0f);
	}
	return Vector4(0.f);
}


FORCEINLINE Vector4 Vector4::GetUnsafeNormal3() const
{
	const float Scale = Math::InvSqrt(X*X + Y*Y + Z*Z);
	return Vector4(X*Scale, Y*Scale, Z*Scale, 0.0f);
}


FORCEINLINE float Vector4::Size3() const
{
	return Math::Sqrt(X*X + Y*Y + Z*Z);
}


FORCEINLINE float Vector4::SizeSquared3() const
{
	return X*X + Y*Y + Z*Z;
}


FORCEINLINE bool Vector4::IsUnit3(float LengthSquaredTolerance) const
{
	return Math::Abs(1.0f - SizeSquared3()) < LengthSquaredTolerance;
}


FORCEINLINE bool Vector4::ContainsNaN() const
{
	return (Math::IsNaN(X) || !Math::IsFinite(X) ||
		Math::IsNaN(Y) || !Math::IsFinite(Y) ||
		Math::IsNaN(Z) || !Math::IsFinite(Z) ||
		Math::IsNaN(W) || !Math::IsFinite(W));
}


FORCEINLINE bool Vector4::IsNearlyZero3(float Tolerance) const
{
	return
		Math::Abs(X) < Tolerance
		&&	Math::Abs(Y) < Tolerance
		&&	Math::Abs(Z) < Tolerance;
}


FORCEINLINE Vector4 Vector4::Reflect3(const Vector4& Normal) const
{
	return 2.0f * Dot3(*this, Normal) * Normal - *this;
}


FORCEINLINE Vector4 Vector4::operator*=(const Vector4& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;
	return *this;
}


FORCEINLINE Vector4 Vector4::operator/=(const Vector4& V)
{
	X /= V.X; Y /= V.Y; Z /= V.Z; W /= V.W;
	return *this;
}


FORCEINLINE Vector4 Vector4::operator*=(float S)
{
	X *= S; Y *= S; Z *= S; W *= S;
	return *this;
}


FORCEINLINE Vector4 Vector4::operator/(const Vector4& V) const
{
	return Vector4(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
}
