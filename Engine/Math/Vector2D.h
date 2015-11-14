#pragma once
#include "../Config/RayConifg.h"
#include "../Config/WindowPlatform.h"
#include "Vector.h"
#include "MathUtility.h"

/**
* A vector in 2-D space composed of components (X, Y) with floating point precision.
*/
struct Vector2D
{
	/** Vector's X component. */
	float X;

	/** Vector's Y component. */
	float Y;

public:

	/** Global 2D zero vector constant (0,0) */
	static const Vector2D ZeroVector;

	/** Global 2D unit vector constant (1,1) */
	static const Vector2D UnitVector;

public:

	/**
	* Default constructor (no initialization).
	*/
	FORCEINLINE Vector2D() { }

	/**
	* Constructor using initial values for each component.
	*
	* @param InX X coordinate.
	* @param InY Y coordinate.
	*/
	FORCEINLINE Vector2D(float InX, float InY);

	/**
	* Constructs a vector from an Vector.
	* Copies the X and Y components from the Vector.
	*
	* @param V Vector to copy from.
	*/
	explicit FORCEINLINE Vector2D(const Vector& V);

public:

	/**
	* Gets the result of adding two vectors together.
	*
	* @param V The other vector to add to this.
	* @return The result of adding the vectors together.
	*/
	FORCEINLINE Vector2D operator+(const Vector2D& V) const;

	/**
	* Gets the result of subtracting a vector from this one.
	*
	* @param V The other vector to subtract from this.
	* @return The result of the subtraction.
	*/
	FORCEINLINE Vector2D operator-(const Vector2D& V) const;

	/**
	* Gets the result of scaling the vector (multiplying each component by a value).
	*
	* @param Scale How much to scale the vector by.
	* @return The result of scaling this vector.
	*/
	FORCEINLINE Vector2D operator*(float Scale) const;

	/**
	* Gets the result of dividing each component of the vector by a value.
	*
	* @param Scale How much to divide the vector by.
	* @return The result of division on this vector.
	*/
	Vector2D operator/(float Scale) const;

	/**
	* Gets the result of this vector + float A.
	*
	* @param A		Float to add to each component.
	* @return		The result of this vector + float A.
	*/
	FORCEINLINE Vector2D operator+(float A) const;

	/**
	* Gets the result of subtracting from each component of the vector.
	*
	* @param A		Float to subtract from each component
	* @return		The result of this vector - float A.
	*/
	FORCEINLINE Vector2D operator-(float A) const;

	/**
	* Gets the result of component-wise multiplication of this vector by another.
	*
	* @param V The other vector to multiply this by.
	* @return The result of the multiplication.
	*/
	FORCEINLINE Vector2D operator*(const Vector2D& V) const;

	/**
	* Gets the result of component-wise division of this vector by another.
	*
	* @param V The other vector to divide this by.
	* @return The result of the division.
	*/
	Vector2D operator/(const Vector2D& V) const;

	/**
	* Calculates dot product of this vector and another.
	*
	* @param V The other vector.
	* @return The dot product.
	*/
	FORCEINLINE float operator|(const Vector2D& V) const;

	/**
	* Calculates cross product of this vector and another.
	*
	* @param V The other vector.
	* @return The cross product.
	*/
	FORCEINLINE float operator^(const Vector2D& V) const;

public:

	/**
	* Compares this vector against another for equality.
	*
	* @param V The vector to compare against.
	* @return true if the two vectors are equal, otherwise false.
	*/
	bool operator==(const Vector2D& V) const;

	/**
	* Compares this vector against another for inequality.
	*
	* @param V The vector to compare against.
	* @return true if the two vectors are not equal, otherwise false.
	*/
	bool operator!=(const Vector2D& V) const;

	/**
	* Checks whether both components of this vector are less than another.
	*
	* @param Other The vector to compare against.
	* @return true if this is the smaller vector, otherwise false.
	*/
	bool operator<(const Vector2D& Other) const;

	/**
	* Checks whether both components of this vector are greater than another.
	*
	* @param Other The vector to compare against.
	* @return true if this is the larger vector, otherwise false.
	*/
	bool operator>(const Vector2D& Other) const;

	/**
	* Checks whether both components of this vector are less than or equal to another.
	*
	* @param Other The vector to compare against.
	* @return true if this vector is less than or equal to the other vector, otherwise false.
	*/
	bool operator<=(const Vector2D& Other) const;

	/**
	* Checks whether both components of this vector are greater than or equal to another.
	*
	* @param Other The vector to compare against.
	* @return true if this vector is greater than or equal to the other vector, otherwise false.
	*/
	bool operator>=(const Vector2D& Other) const;

	/**
	* Gets a negated copy of the vector.
	*
	* @return A negated copy of the vector.
	*/
	FORCEINLINE Vector2D operator-() const;

	/**
	* Adds another vector to this.
	*
	* @param V The other vector to add.
	* @return Copy of the vector after addition.
	*/
	FORCEINLINE Vector2D operator+=(const Vector2D& V);

	/**
	* Subtracts another vector from this.
	*
	* @param V The other vector to subtract.
	* @return Copy of the vector after subtraction.
	*/
	FORCEINLINE Vector2D operator-=(const Vector2D& V);

	/**
	* Scales this vector.
	*
	* @param Scale The scale to multiply vector by.
	* @return Copy of the vector after scaling.
	*/
	FORCEINLINE Vector2D operator*=(float Scale);

	/**
	* Divides this vector.
	*
	* @param V What to divide vector by.
	* @return Copy of the vector after division.
	*/
	Vector2D operator/=(float V);

	/**
	* Multiplies this vector with another vector, using component-wise multiplication.
	*
	* @param V The vector to multiply with.
	* @return Copy of the vector after multiplication.
	*/
	Vector2D operator*=(const Vector2D& V);

	/**
	* Divides this vector by another vector, using component-wise division.
	*
	* @param V The vector to divide by.
	* @return Copy of the vector after division.
	*/
	Vector2D operator/=(const Vector2D& V);

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
	* @return copy of component value.
	*/
	float operator[](int32 Index) const;

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
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

public:

	/**
	* Calculates the dot product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The dot product.
	*/
	FORCEINLINE static float DotProduct(const Vector2D& A, const Vector2D& B);

	/**
	* Squared distance between two 2D points.
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The squared distance between two 2D points.
	*/
	FORCEINLINE static float DistSquared(const Vector2D& V1, const Vector2D& V2);

	/**
	* Distance between two 2D points.
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The squared distance between two 2D points.
	*/
	FORCEINLINE static float Distance(const Vector2D& V1, const Vector2D& V2);

	/**
	* Calculate the cross product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The cross product.
	*/
	FORCEINLINE static float CrossProduct(const Vector2D& A, const Vector2D& B);

	/**
	* Checks for equality with error-tolerant comparison.
	*
	* @param V The vector to compare.
	* @param Tolerance Error tolerance.
	* @return true if the vectors are equal within specified tolerance, otherwise false.
	*/
	bool Equals(const Vector2D& V, float Tolerance) const;

	/**
	* Set the values of the vector directly.
	*
	* @param InX New X coordinate.
	* @param InY New Y coordinate.
	*/
	void Set(float InX, float InY);

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
	* Gets a normalized copy of the vector, checking it is safe to do so based on the length.
	* Returns zero vector if vector length is too small to safely normalize.
	*
	* @param Tolerance Minimum squared length of vector for normalization.
	* @return A normalized copy of the vector if safe, (0,0) otherwise.
	*/
	Vector2D GetSafeNormal(float Tolerance = SMALL_NUMBER) const;

	/**
	* Normalize this vector in-place if it is large enough, set it to (0,0) otherwise.
	*
	* @param Tolerance Minimum squared length of vector for normalization.
	* @see GetSafeNormal()
	*/
	void Normalize(float Tolerance = SMALL_NUMBER);

	/**
	* Checks whether vector is near to zero within a specified tolerance.
	*
	* @param Tolerance Error tolerance.
	* @return true if vector is in tolerance to zero, otherwise false.
	*/
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Checks whether all components of the vector are exactly zero.
	*
	* @return true if vector is exactly zero, otherwise false.
	*/
	bool IsZero() const;

	/**
	* Creates a copy of this vector with both axes clamped to the given range.
	* @return New vector with clamped axes.
	*/
	Vector2D ClampAxes(float MinAxisVal, float MaxAxisVal) const;

	/**
	* Get a copy of the vector as sign only.
	* Each component is set to +1 or -1, with the sign of zero treated as +1.
	*
	* @param A copy of the vector with each component set to +1 or -1
	*/
	FORCEINLINE Vector2D GetSignVector() const;

	/**
	* Utility to check if there are any NaNs in this vector.
	*
	* @return true if there are any NaNs in this vector, otherwise false.
	*/
	FORCEINLINE bool ContainsNaN() const
	{
		return (Math::IsNaN(X) || !Math::IsFinite(X) ||
			Math::IsNaN(Y) || !Math::IsFinite(Y));
	}

	/** Converts spherical coordinates on the unit sphere into a Cartesian unit length vector. */
	inline Vector SphericalToUnitCartesian() const;
};


/* Vector2D inline functions
*****************************************************************************/

FORCEINLINE Vector2D operator*(float Scale, const Vector2D& V)
{
	return V.operator*(Scale);
}


FORCEINLINE Vector2D::Vector2D(float InX, float InY)
	: X(InX), Y(InY)
{ }


FORCEINLINE Vector2D Vector2D::operator+(const Vector2D& V) const
{
	return Vector2D(X + V.X, Y + V.Y);
}


FORCEINLINE Vector2D Vector2D::operator-(const Vector2D& V) const
{
	return Vector2D(X - V.X, Y - V.Y);
}


FORCEINLINE Vector2D Vector2D::operator*(float Scale) const
{
	return Vector2D(X * Scale, Y * Scale);
}


FORCEINLINE Vector2D Vector2D::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return Vector2D(X * RScale, Y * RScale);
}


FORCEINLINE Vector2D Vector2D::operator+(float A) const
{
	return Vector2D(X + A, Y + A);
}


FORCEINLINE Vector2D Vector2D::operator-(float A) const
{
	return Vector2D(X - A, Y - A);
}


FORCEINLINE Vector2D Vector2D::operator*(const Vector2D& V) const
{
	return Vector2D(X * V.X, Y * V.Y);
}


FORCEINLINE Vector2D Vector2D::operator/(const Vector2D& V) const
{
	return Vector2D(X / V.X, Y / V.Y);
}


FORCEINLINE float Vector2D::operator|(const Vector2D& V) const
{
	return X*V.X + Y*V.Y;
}


FORCEINLINE float Vector2D::operator^(const Vector2D& V) const
{
	return X*V.Y - Y*V.X;
}


FORCEINLINE float Vector2D::DotProduct(const Vector2D& A, const Vector2D& B)
{
	return A | B;
}


FORCEINLINE float Vector2D::DistSquared(const Vector2D &V1, const Vector2D &V2)
{
	return Math::Square(V2.X - V1.X) + Math::Square(V2.Y - V1.Y);
}


FORCEINLINE float Vector2D::Distance(const Vector2D& V1, const Vector2D& V2)
{
	return Math::Sqrt(Vector2D::DistSquared(V1, V2));
}


FORCEINLINE float Vector2D::CrossProduct(const Vector2D& A, const Vector2D& B)
{
	return A ^ B;
}


FORCEINLINE bool Vector2D::operator==(const Vector2D& V) const
{
	return X == V.X && Y == V.Y;
}


FORCEINLINE bool Vector2D::operator!=(const Vector2D& V) const
{
	return X != V.X || Y != V.Y;
}


FORCEINLINE bool Vector2D::operator<(const Vector2D& Other) const
{
	return X < Other.X && Y < Other.Y;
}


FORCEINLINE bool Vector2D::operator>(const Vector2D& Other) const
{
	return X > Other.X && Y > Other.Y;
}


FORCEINLINE bool Vector2D::operator<=(const Vector2D& Other) const
{
	return X <= Other.X && Y <= Other.Y;
}


FORCEINLINE bool Vector2D::operator>=(const Vector2D& Other) const
{
	return X >= Other.X && Y >= Other.Y;
}


FORCEINLINE bool Vector2D::Equals(const Vector2D& V, float Tolerance) const
{
	return Math::Abs(X - V.X) < Tolerance && Math::Abs(Y - V.Y) < Tolerance;
}


FORCEINLINE Vector2D Vector2D::operator-() const
{
	return Vector2D(-X, -Y);
}


FORCEINLINE Vector2D Vector2D::operator+=(const Vector2D& V)
{
	X += V.X; Y += V.Y;
	return *this;
}


FORCEINLINE Vector2D Vector2D::operator-=(const Vector2D& V)
{
	X -= V.X; Y -= V.Y;
	return *this;
}


FORCEINLINE Vector2D Vector2D::operator*=(float Scale)
{
	X *= Scale; Y *= Scale;
	return *this;
}


FORCEINLINE Vector2D Vector2D::operator/=(float V)
{
	const float RV = 1.f / V;
	X *= RV; Y *= RV;
	return *this;
}


FORCEINLINE Vector2D Vector2D::operator*=(const Vector2D& V)
{
	X *= V.X; Y *= V.Y;
	return *this;
}


FORCEINLINE Vector2D Vector2D::operator/=(const Vector2D& V)
{
	X /= V.X; Y /= V.Y;
	return *this;
}


FORCEINLINE float& Vector2D::operator[](int32 Index)
{
	return ((Index == 0) ? X : Y);
}


FORCEINLINE float Vector2D::operator[](int32 Index) const
{
	return ((Index == 0) ? X : Y);
}


FORCEINLINE void Vector2D::Set(float InX, float InY)
{
	X = InX;
	Y = InY;
}


FORCEINLINE float Vector2D::GetMax() const
{
	return Math::Max(X, Y);
}


FORCEINLINE float Vector2D::GetAbsMax() const
{
	return Math::Max(Math::Abs(X), Math::Abs(Y));
}


FORCEINLINE float Vector2D::GetMin() const
{
	return Math::Min(X, Y);
}


FORCEINLINE float Vector2D::Size() const
{
	return Math::Sqrt(X*X + Y*Y);
}


FORCEINLINE float Vector2D::SizeSquared() const
{
	return X*X + Y*Y;
}


FORCEINLINE Vector2D Vector2D::GetSafeNormal(float Tolerance) const
{
	const float SquareSum = X*X + Y*Y;
	if (SquareSum > Tolerance)
	{
		const float Scale = Math::InvSqrt(SquareSum);
		return Vector2D(X*Scale, Y*Scale);
	}
	return Vector2D(0.f, 0.f);
}


FORCEINLINE void Vector2D::Normalize(float Tolerance)
{
	const float SquareSum = X*X + Y*Y;
	if (SquareSum > Tolerance)
	{
		const float Scale = Math::InvSqrt(SquareSum);
		X *= Scale;
		Y *= Scale;
		return;
	}
	X = 0.0f;
	Y = 0.0f;
}


FORCEINLINE bool Vector2D::IsNearlyZero(float Tolerance) const
{
	return	Math::Abs(X)<Tolerance
		&&	Math::Abs(Y)<Tolerance;
}


FORCEINLINE bool Vector2D::IsZero() const
{
	return X == 0.f && Y == 0.f;
}


FORCEINLINE float& Vector2D::Component(int32 Index)
{
	return (&X)[Index];
}


FORCEINLINE float Vector2D::Component(int32 Index) const
{
	return (&X)[Index];
}


FORCEINLINE FIntPoint Vector2D::IntPoint() const
{
	return FIntPoint(Math::RoundToInt(X), Math::RoundToInt(Y));
}


FORCEINLINE Vector2D Vector2D::ClampAxes(float MinAxisVal, float MaxAxisVal) const
{
	return Vector2D(Math::Clamp(X, MinAxisVal, MaxAxisVal), Math::Clamp(Y, MinAxisVal, MaxAxisVal));
}


FORCEINLINE Vector2D Vector2D::GetSignVector() const
{
	return Vector2D
		(
		Math::FloatSelect(X, 1.f, -1.f),
		Math::FloatSelect(Y, 1.f, -1.f)
		);
}