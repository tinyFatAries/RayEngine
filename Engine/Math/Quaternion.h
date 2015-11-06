//===========================================================================
// Quaternion: .
//===========================================================================

#pragma once
#include "MathUtility.h"
#include "../Config/RayConifg.h"
#include "../Tools/RayUtils.h"
#include "Axis.h"
#include "Matrix.h"
#include "Vector.h"
#include "Vector4.h"
#include "RayMathDirectX.h"
/**
* Floating point quaternion that can represent a rotation about an axis in 3-D space.
* The X, Y, Z, W components also double as the Axis/Angle format.
*
* Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
* first applies B then A to any subsequent transformation (right first, then left).
* Note that this is the opposite order of FTransform multiplication.
*
* Example: LocalToWorld = (LocalToWorld * DeltaRotation) will change rotation in local space by DeltaRotation.
* Example: LocalToWorld = (DeltaRotation * LocalToWorld) will change rotation in world space by DeltaRotation.
*/
struct Quaternion
{
public:

	/** Holds the quaternion's X-component. */
	float X;

	/** Holds the quaternion's Y-component. */
	float Y;

	/** Holds the quaternion's Z-component. */
	float Z;

	/** Holds the quaternion's W-component. */
	float W;

public:

	//Identity quaternion
	static const Quaternion Identity;

public:

	/**
	* Default constructor (no initialization).
	*/
	FORCEINLINE Quaternion() { }

	/**
	* Constructor.
	*
	* @param InX X component of the quaternion
	* @param InY Y component of the quaternion
	* @param InZ Z component of the quaternion
	* @param InW W component of the quaternion
	*/
	FORCEINLINE Quaternion(float InX, float InY, float InZ, float InW);

	/**
	* Copy constructor.
	*
	* @param Q A Quaternion object to use to create new quaternion from.
	*/
	FORCEINLINE Quaternion(const Quaternion& Q);

	/**
	* Creates and initializes a new quaternion from the given matrix.
	*
	* @param M The rotation matrix to initialize from.
	*/
	explicit Quaternion(const Matrix& M);

	/**
	* Creates and initializes a new quaternion from the given rotator.
	*
	* @param R The rotator to initialize from.
	*/
	//explicit Quaternion(const Rotator& R);

	/**
	* Creates and initializes a new quaternion from the a rotation around the given axis.
	*
	* @param Axis assumed to be a normalized vector
	* @param Angle angle to rotate above the given axis (in radians)
	*/
	Quaternion(Vector Axis, float AngleRad);

public:

	/**
	* Gets the result of adding a Quaternion to this.
	* This is a component-wise addition; composing quaternions should be done via multiplication.
	*
	* @param Q The Quaternion to add.
	* @return The result of addition.
	*/
	FORCEINLINE Quaternion operator+(const Quaternion& Q) const;

	/**
	* Adds to this quaternion.
	* This is a component-wise addition; composing quaternions should be done via multiplication.
	*
	* @param Other The quaternion to add to this.
	* @return Result after addition.
	*/
	FORCEINLINE Quaternion operator+=(const Quaternion& Q);

	/**
	* Gets the result of subtracting a Quaternion to this.
	* This is a component-wise subtraction; composing quaternions should be done via multiplication.
	*
	* @param Q The Quaternion to subtract.
	* @return The result of subtraction.
	*/
	FORCEINLINE Quaternion operator-(const Quaternion& Q) const;

	/**
	* Checks whether another Quaternion is equal to this, within specified tolerance.
	*
	* @param Q The other Quaternion.
	* @param Tolerance Error Tolerance.
	* @return true if two Quaternion are equal, within specified tolerance, otherwise false.
	*/
	FORCEINLINE bool Equals(const Quaternion& Q, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Subtracts another quaternion from this.
	* This is a component-wise subtraction; composing quaternions should be done via multiplication.
	*
	* @param Q The other quaternion.
	* @return reference to this after subtraction.
	*/
	FORCEINLINE Quaternion operator-=(const Quaternion& Q);

	/**
	* Gets the result of multiplying this by another quaternion (this * Q).
	*
	* Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	* first applies B then A to any subsequent transformation (right first, then left).
	*
	* @param Q The Quaternion to multiply this by.
	* @return The result of multiplication (this * Q).
	*/
	FORCEINLINE Quaternion operator*(const Quaternion& Q) const;

	/**
	* Multiply this by a quaternion (this = this * Q).
	*
	* Order matters when composing quaternions: C = A * B will yield a quaternion C that logically
	* first applies B then A to any subsequent transformation (right first, then left).
	*
	* @param Q the quaternion to multiply this by.
	* @return The result of multiplication (this * Q).
	*/
	FORCEINLINE Quaternion operator*=(const Quaternion& Q);

	/**
	* Rotate a vector by this quaternion.
	*
	* @param V the vector to be rotated
	* @return vector after rotation
	* @see RotateVector()
	*/
	Vector operator*(const Vector& V) const;

	/**
	* Multiply this by a matrix.
	* This matrix conversion came from
	* http://www.m-hikari.com/ija/ija-password-2008/ija-password17-20-2008/aristidouIJA17-20-2008.pdf
	* used for non-uniform scaling transform.
	*
	* @param M Matrix to multiply by.
	* @return Matrix result after multiplication.
	*/
	Matrix operator*(const Matrix& M) const;

	/**
	* Multiply this quaternion by a scaling factor.
	*
	* @param Scale The scaling factor.
	* @return a reference to this after scaling.
	*/
	FORCEINLINE Quaternion operator*=(const float Scale);

	/**
	* Get the result of scaling this rotator.
	*
	* @param Scale The scaling factor.
	* @return The result of scaling.
	*/
	FORCEINLINE Quaternion operator*(const float Scale) const;

	/**
	* Divide this quaternion by scale.
	*
	* @param Scale What to divide by.
	* @return new Quaternion of this after division by scale.
	*/
	FORCEINLINE Quaternion operator/(const float Scale) const;

	/**
	* Checks whether two quaternions are identical.
	* This is an exact comparison per-component;see Equals() for a comparison
	* that allows for a small error tolerance and flipped axes of rotation.
	*
	* @param Q The other quaternion.
	* @return true if two quaternion are identical, otherwise false.
	* @see Equals()
	*/
	bool operator==(const Quaternion& Q) const;

	/**
	* Checks whether two quaternions are not identical.
	*
	* @param Q The other quaternion.
	* @return true if two quaternion are not identical, otherwise false.
	*/
	bool operator!=(const Quaternion& Q) const;

	/**
	* Calculates dot product of two quaternions.
	*
	* @param Q The other quaternions.
	* @return The dot product.
	*/
	float operator|(const Quaternion& Q) const;

public:

	/**
	* Convert a vector of floating-point Euler angles (in degrees) into a Quaternion.
	*
	* @param Euler the Euler angles
	* @return constructed Quaternion
	*/
	static Quaternion MakeFromEuler(const Vector& Euler);

	/** Convert a Quaternion into floating-point Euler angles (in degrees). */
	Vector Euler() const;

	/**
	* Normalize this quaternion if it is large enough.
	*
	* @param Tolerance Minimum squared length of vector for normalization.
	*/
	FORCEINLINE void Normalize(float Tolerance = SMALL_NUMBER);

	// Return true if this quaternion is normalized
	bool IsNormalized() const;

	/**
	* Get the length of this quaternion.
	*
	* @return The length of this quaternion.
	*/
	FORCEINLINE float Size() const;

	/**
	* Get the length squared of this quaternion.
	*
	* @return The length of this quaternion.
	*/
	FORCEINLINE float SizeSquared() const;

	/**
	* get the axis and angle of rotation of this quaternion
	*
	* @param Axis{out] vector of axis of the quaternion
	* @param Angle{out] angle of the quaternion
	* @warning : assumes normalized quaternions.
	*/
	void ToAxisAndAngle(Vector& Axis, float& Angle) const;

	/**
	* Rotate a vector by this quaternion.
	*
	* @param V the vector to be rotated
	* @return vector after rotation
	*/
	Vector RotateVector(Vector V) const;

	/**
	* @return quaternion with W=0 and V=theta*v.
	*/
	Quaternion Log() const;

	/**
	* @note Exp should really only be used after Log.
	* Assumes a quaternion with W=0 and V=theta*v (where |v| = 1).
	* Exp(q) = (sin(theta)*v, cos(theta))
	*/
	Quaternion Exp() const;

	FORCEINLINE Quaternion Inverse() const;

	/**
	* Enforce that the delta between this Quaternion and another one represents
	* the shortest possible rotation angle
	*/
	void EnforceShortestArcWith(const Quaternion& OtherQuat);

	/** Get X Rotation Axis. */
	FORCEINLINE Vector GetAxisX() const;

	/** Get Y Rotation Axis. */
	FORCEINLINE Vector GetAxisY() const;

	/** Get Z Rotation Axis. */
	FORCEINLINE Vector GetAxisZ() const;

	/** @return rotator representation of this quaternion */
	//Rotator Rotator() const;

	/** @return Vector of the axis of the quaternion */
	FORCEINLINE Vector GetRotationAxis() const;

	/**
	* Utility to check if there are any NaNs in this Quaternion.
	*
	* @return true if there are any NaNs in this Quaternion, otherwise false.
	*/
	bool ContainsNaN() const;

public:

	/**
	* Generates the 'smallest' (geodesic) rotation between these two vectors.
	*/
	static Quaternion FindBetween(const Vector& vec1, const Vector& vec2);

	/**
	* Error measure (angle) between two quaternions, ranged [0..1].
	* Returns the hypersphere-angle between two quaternions; alignment shouldn't matter, though
	* @note normalized input is expected.
	*/
	static FORCEINLINE float Error(const Quaternion& Q1, const Quaternion& Q2);

	/**
	* Quaternion::Error with auto-normalization.
	*/
	static FORCEINLINE float ErrorAutoNormalize(const Quaternion& A, const Quaternion& B);

	/**
	* Fast Linear Quaternion Interpolation.
	* Result is NOT normalized.
	*/
	static FORCEINLINE Quaternion FastLerp(const Quaternion& A, const Quaternion& B, const float Alpha);

	/**
	* Bi-Linear Quaternion interpolation.
	* Result is NOT normalized.
	*/
	static FORCEINLINE Quaternion FastBilerp(const Quaternion& P00, const Quaternion& P10, const Quaternion& P01, const Quaternion& P11, float FracX, float FracY);


	/** Spherical interpolation. Will correct alignment. Output is not normalized. */
	static Quaternion Slerp(const Quaternion &Quat1, const Quaternion &Quat2, float Slerp);

	/**
	* Simpler Slerp that doesn't do any checks for 'shortest distance' etc.
	* We need this for the cubic interpolation stuff so that the multiple Slerps dont go in different directions.
	*/
	static Quaternion SlerpFullPath(const Quaternion &quat1, const Quaternion &quat2, float Alpha);

	/** Given start and end quaternions of quat1 and quat2, and tangents at those points tang1 and tang2, calculate the point at Alpha (between 0 and 1) between them. */
	static Quaternion Squad(const Quaternion& quat1, const Quaternion& tang1, const Quaternion& quat2, const Quaternion& tang2, float Alpha);

	/**
	* Calculate tangents between given points
	*
	* @param PrevP quaternion at P-1
	* @param P quaternion to return the tangent
	* @param NextP quaternion P+1
	* @param Tension @todo document
	* @param OutTan Out control point
	*/
	static void CalcTangents(const Quaternion& PrevP, const Quaternion& P, const Quaternion& NextP, float Tension, Quaternion& OutTan);

};
/* Quaternion inline functions
*****************************************************************************/


FORCEINLINE Quaternion::Quaternion(float InX, float InY, float InZ, float InW)
	: X(InX)
	, Y(InY)
	, Z(InZ)
	, W(InW)
{
}


FORCEINLINE Quaternion::Quaternion(const Quaternion& Q)
	: X(Q.X)
	, Y(Q.Y)
	, Z(Q.Z)
	, W(Q.W)
{ }


FORCEINLINE Quaternion::Quaternion(Vector Axis, float AngleRad)
{
	const float half_a = 0.5f * AngleRad;
	const float s = Math::Sin(half_a);
	const float c = Math::Cos(half_a);

	X = s * Axis.X;
	Y = s * Axis.Y;
	Z = s * Axis.Z;
	W = c;

}

inline Quaternion::Quaternion(const Matrix& M)
{
	// If Matrix is NULL, return Identity quaternion. If any of them is 0, you won't be able to construct rotation
	// if you have two plane at least, we can reconstruct the frame using cross product, but that's a bit expensive op to do here
	// for now, if you convert to matrix from 0 scale and convert back, you'll lose rotation. Don't do that. 
	if (M.GetScaledAxis(EAxis::X).IsNearlyZero() || M.GetScaledAxis(EAxis::Y).IsNearlyZero() || M.GetScaledAxis(EAxis::Z).IsNearlyZero())
	{
		*this = Quaternion::Identity;
		return;
	}

#ifdef DEBUG_MODE 
	// Make sure the Rotation part of the Matrix is unit length.
	// Changed to this (same as RemoveScaling) from RotDeterminant as using two different ways of checking unit length matrix caused inconsistency. 
	if (!((Math::Abs(1.f - M.GetScaledAxis(EAxis::X).SizeSquared()) <= KINDA_SMALL_NUMBER) 
		&& (Math::Abs(1.f - M.GetScaledAxis(EAxis::Y).SizeSquared()) <= KINDA_SMALL_NUMBER) 
		&& (Math::Abs(1.f - M.GetScaledAxis(EAxis::Z).SizeSquared()) <= KINDA_SMALL_NUMBER)))
	{
		*this = Quaternion::Identity;
		return;
	}
#endif

	//const MeReal *const t = (MeReal *) tm;
	float	s;

	// Check diagonal (trace)
	const float tr = M.M[0][0] + M.M[1][1] + M.M[2][2];

	if (tr > 0.0f)
	{
		float InvS = Math::InvSqrt(tr + 1.f);
		this->W = 0.5f * (1.f / InvS);
		s = 0.5f * InvS;

		this->X = (M.M[1][2] - M.M[2][1]) * s;
		this->Y = (M.M[2][0] - M.M[0][2]) * s;
		this->Z = (M.M[0][1] - M.M[1][0]) * s;
	}
	else
	{
		// diagonal is negative
		int32 i = 0;

		if (M.M[1][1] > M.M[0][0])
			i = 1;

		if (M.M[2][2] > M.M[i][i])
			i = 2;

		static const int32 nxt[3] = { 1, 2, 0 };
		const int32 j = nxt[i];
		const int32 k = nxt[j];

		s = M.M[i][i] - M.M[j][j] - M.M[k][k] + 1.0f;

		float InvS = Math::InvSqrt(s);

		float qt[4];
		qt[i] = 0.5f * (1.f / InvS);

		s = 0.5f * InvS;

		qt[3] = (M.M[j][k] - M.M[k][j]) * s;
		qt[j] = (M.M[i][j] + M.M[j][i]) * s;
		qt[k] = (M.M[i][k] + M.M[k][i]) * s;

		this->X = qt[0];
		this->Y = qt[1];
		this->Z = qt[2];
		this->W = qt[3];
	}
}

//FORCEINLINE Quaternion::Quaternion(const Rotator& R)
//{
//	*this = R.Quaternion();
//}


inline Vector Quaternion::operator*(const Vector& V) const
{
	Quaternion VQ(V.X, V.Y, V.Z, 0.f);
	Quaternion VT, VR;
	Quaternion I = Inverse();
	VectorQuaternionMultiply(&VT, this, &VQ);
	VectorQuaternionMultiply(&VR, &VT, &I);

	return Vector(VR.X, VR.Y, VR.Z);
}


inline Matrix Quaternion::operator*(const Matrix& M) const
{
	Matrix Result;
	Quaternion VT, VR;
	Quaternion Inv = Inverse();
	for (int32 I = 0; I<4; ++I)
	{
		Quaternion VQ(M.M[I][0], M.M[I][1], M.M[I][2], M.M[I][3]);
		VectorQuaternionMultiply(&VT, this, &VQ);
		VectorQuaternionMultiply(&VR, &VT, &Inv);
		Result.M[I][0] = VR.X;
		Result.M[I][1] = VR.Y;
		Result.M[I][2] = VR.Z;
		Result.M[I][3] = VR.W;
	}

	return Result;
}


//inline Rotator Quaternion::Rotator() const
//{
//#if USE_MATRIX_ROTATOR 
//	// if you think this function is problem, you can undo previous matrix rotator by returning RotatorFromMatrix
//	Rotator RotatorFromMatrix = QuaternionRotationTranslationMatrix(*this, Vector::ZeroVector).Rotator();
//	checkSlow(IsNormalized());
//#endif
//
//	static float RAD_TO_DEG = 180.f / PI;
//
//	Rotator RotatorFromQuat;
//	float SingularityTest = Z*X - W*Y;
//	float Pitch = Math::Asin(2 * (SingularityTest));
//
//	RotatorFromQuat.Yaw = Math::Atan2(2.f*(W*Z + X*Y), (1 - 2.f*(Math::Square(Y) + Math::Square(Z))))*RAD_TO_DEG;
//
//	// reference 
//	// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
//	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
//
//	// this value was found from experience, the above websites recommend different values
//	// but that isn't the case for us, so I went through different testing, and finally found the case 
//	// where both of world lives happily. 
//#define SINGULARITY_THRESHOLD	0.4999995f
//
//	if (SingularityTest < -SINGULARITY_THRESHOLD)
//	{
//		RotatorFromQuat.Roll = -RotatorFromQuat.Yaw - 2.f* Math::Atan2(X, W) * RAD_TO_DEG;
//		RotatorFromQuat.Pitch = 270.f;
//	}
//	else if (SingularityTest > SINGULARITY_THRESHOLD)
//	{
//		RotatorFromQuat.Roll = RotatorFromQuat.Yaw - 2.f* Math::Atan2(X, W) * RAD_TO_DEG;
//		RotatorFromQuat.Pitch = 90.f;
//	}
//	else
//	{
//		RotatorFromQuat.Roll = Math::Atan2(-2.f*(W*X + Y*Z), (1 - 2.f*(Math::Square(X) + Math::Square(Y))))*RAD_TO_DEG;
//		RotatorFromQuat.Pitch = Rotator::ClampAxis(Pitch*RAD_TO_DEG); //clamp it so within 360 - this is for if below
//	}
//
//	RotatorFromQuat.Normalize();
//
//#if USE_MATRIX_ROTATOR
//	RotatorFromMatrix = RotatorFromMatrix.Clamp();
//
//	// this Euler is degree, so less 1 is negligible
//	if (!DebugRotatorEquals(RotatorFromQuat, RotatorFromMatrix, 0.1f))
//	{
//		FPlatformMisc::LowLevelOutputDebugStringf(TEXT("WRONG: (Singularity: %.9f) RotationMatrix (%s), RotationQuat(%s)"), SingularityTest, *RotatorFromMatrix.ToString(), *RotatorFromQuat.ToString());
//	}
//
//	return RotatorFromMatrix;
//#else
//	return RotatorFromQuat;
//#endif
//}


FORCEINLINE Quaternion Quaternion::operator+(const Quaternion& Q) const
{
	return Quaternion(X + Q.X, Y + Q.Y, Z + Q.Z, W + Q.W);
}


FORCEINLINE Quaternion Quaternion::operator+=(const Quaternion& Q)
{
	this->X += Q.X;
	this->Y += Q.Y;
	this->Z += Q.Z;
	this->W += Q.W;

	return *this;
}


FORCEINLINE Quaternion Quaternion::operator-(const Quaternion& Q) const
{
	return Quaternion(X - Q.X, Y - Q.Y, Z - Q.Z, W - Q.W);
}


FORCEINLINE bool Quaternion::Equals(const Quaternion& Q, float Tolerance) const
{
	return (Math::Abs(X - Q.X) < Tolerance && Math::Abs(Y - Q.Y) < Tolerance && Math::Abs(Z - Q.Z) < Tolerance && Math::Abs(W - Q.W) < Tolerance)
		|| (Math::Abs(X + Q.X) < Tolerance && Math::Abs(Y + Q.Y) < Tolerance && Math::Abs(Z + Q.Z) < Tolerance && Math::Abs(W + Q.W) < Tolerance);
}


FORCEINLINE Quaternion Quaternion::operator-=(const Quaternion& Q)
{
	this->X -= Q.X;
	this->Y -= Q.Y;
	this->Z -= Q.Z;
	this->W -= Q.W;

	return *this;
}


FORCEINLINE Quaternion Quaternion::operator*(const Quaternion& Q) const
{
	Quaternion Result;
	VectorQuaternionMultiply(&Result, this, &Q);

	return Result;
}


FORCEINLINE Quaternion Quaternion::operator*=(const Quaternion& Q)
{
	/**
	* Now this uses VectorQuaternionMultiply that is optimized per platform.
	*/
	VectorRegister A = VectorLoadAligned(this);
	VectorRegister B = VectorLoadAligned(&Q);
	VectorRegister Result;
	VectorQuaternionMultiply(&Result, &A, &B);
	VectorStoreAligned(Result, this);

	return *this;
}


FORCEINLINE Quaternion Quaternion::operator*=(const float Scale)
{
	X *= Scale;
	Y *= Scale;
	Z *= Scale;
	W *= Scale;

	return *this;
}


FORCEINLINE Quaternion Quaternion::operator*(const float Scale) const
{
	return Quaternion(Scale * X, Scale * Y, Scale * Z, Scale * W);
}


FORCEINLINE Quaternion Quaternion::operator/(const float Scale) const
{
	return Quaternion(X / Scale, Y / Scale, Z / Scale, W / Scale);
}


FORCEINLINE bool Quaternion::operator==(const Quaternion& Q) const
{
	return X == Q.X && Y == Q.Y && Z == Q.Z && W == Q.W;
}


FORCEINLINE bool Quaternion::operator!=(const Quaternion& Q) const
{
	return X != Q.X || Y != Q.Y || Z != Q.Z || W != Q.W;
}


FORCEINLINE float Quaternion::operator|(const Quaternion& Q) const
{
	return X * Q.X + Y * Q.Y + Z * Q.Z + W * Q.W;
}


FORCEINLINE void Quaternion::Normalize(float Tolerance)
{
	const float SquareSum = X * X + Y * Y + Z * Z + W * W;

	if (SquareSum > Tolerance)
	{
		const float Scale = Math::InvSqrt(SquareSum);

		X *= Scale;
		Y *= Scale;
		Z *= Scale;
		W *= Scale;
	}
	else
	{
		*this = Quaternion::Identity;
	}
}


FORCEINLINE bool Quaternion::IsNormalized() const
{
	return (Math::Abs(1.f - SizeSquared()) < THRESH_QUAT_NORMALIZED);
}


FORCEINLINE float Quaternion::Size() const
{
	return Math::Sqrt(X * X + Y * Y + Z * Z + W * W);
}


FORCEINLINE float Quaternion::SizeSquared() const
{
	return (X * X + Y * Y + Z * Z + W * W);
}


FORCEINLINE void Quaternion::ToAxisAndAngle(Vector& Axis, float& Angle) const
{
	Angle = 2.f * Math::Acos(W);
	Axis = GetRotationAxis();
}


FORCEINLINE Vector Quaternion::GetRotationAxis() const
{
	// Ensure we never try to sqrt a neg number
	const float S = Math::Sqrt(Math::Max(1.f - (W * W), 0.f));

	if (S >= 0.0001f)
	{
		return Vector(X / S, Y / S, Z / S);
	}

	return Vector(1.f, 0.f, 0.f);
}


FORCEINLINE Vector Quaternion::RotateVector(Vector V) const
{
	// (q.W*q.W-qv.qv)v + 2(qv.v)qv + 2 q.W (qv x v)

	const Vector qv(X, Y, Z);
	Vector vOut = 2.f * W * (qv ^ V);
	vOut += ((W * W) - (qv | qv)) * V;
	vOut += (2.f * (qv | V)) * qv;

	return vOut;
}


FORCEINLINE Quaternion Quaternion::Inverse() const
{
	ASSERT(IsNormalized());

	return Quaternion(-X, -Y, -Z, W);
}


FORCEINLINE void Quaternion::EnforceShortestArcWith(const Quaternion& OtherQuat)
{
	const float DotResult = (OtherQuat | *this);
	const float Bias = Math::FloatSelect(DotResult, 1.0f, -1.0f);

	X *= Bias;
	Y *= Bias;
	Z *= Bias;
	W *= Bias;
}


FORCEINLINE Vector Quaternion::GetAxisX() const
{
	return RotateVector(Vector(1.f, 0.f, 0.f));
}


FORCEINLINE Vector Quaternion::GetAxisY() const
{
	return RotateVector(Vector(0.f, 1.f, 0.f));
}


FORCEINLINE Vector Quaternion::GetAxisZ() const
{
	return RotateVector(Vector(0.f, 0.f, 1.f));
}


FORCEINLINE float Quaternion::Error(const Quaternion& Q1, const Quaternion& Q2)
{
	const float cosom = Math::Abs(Q1.X * Q2.X + Q1.Y * Q2.Y + Q1.Z * Q2.Z + Q1.W * Q2.W);
	return (Math::Abs(cosom) < 0.9999999f) ? Math::Acos(cosom)*(1.f / PI) : 0.0f;
}


FORCEINLINE float Quaternion::ErrorAutoNormalize(const Quaternion& A, const Quaternion& B)
{
	Quaternion Q1 = A;
	Q1.Normalize();

	Quaternion Q2 = B;
	Q2.Normalize();

	return Quaternion::Error(Q1, Q2);
}


FORCEINLINE Quaternion Quaternion::FastLerp(const Quaternion& A, const Quaternion& B, const float Alpha)
{
	// To ensure the 'shortest route', we make sure the dot product between the both rotations is positive.
	const float DotResult = (A | B);
	const float Bias = Math::FloatSelect(DotResult, 1.0f, -1.0f);
	return (B * Alpha) + (A * (Bias * (1.f - Alpha)));
}


FORCEINLINE Quaternion Quaternion::FastBilerp(const Quaternion& P00, const Quaternion& P10, const Quaternion& P01, const Quaternion& P11, float FracX, float FracY)
{
	return Quaternion::FastLerp(
		Quaternion::FastLerp(P00, P10, FracX),
		Quaternion::FastLerp(P01, P11, FracX),
		FracY
		);
}


FORCEINLINE bool Quaternion::ContainsNaN() const
{
	return (Math::IsNaN(X) || !Math::IsFinite(X) ||
		Math::IsNaN(Y) || !Math::IsFinite(Y) ||
		Math::IsNaN(Z) || !Math::IsFinite(Z) ||
		Math::IsNaN(W) || !Math::IsFinite(W)
		);
}
