//===========================================================================
// Matrix: 
//===========================================================================

#pragma once
#include "MathUtility.h"
#include "NumbericLimits.h"
#include "Axis.h"
#include "Vector.h"
#include "Vector4.h"
#include "RayMathDirectX.h"
#include "../Tools/RayUtils.h"
#include "../Config/WindowPlatform.h"


struct Matrix
{
public:
	union
	{
		float M[4][4];
	};

	// Identity Matrix
	static const Matrix Identity;

	// Constructors.
	Matrix();

	/**
	* Constructor.
	*
	* @param InX X vector
	* @param InY Y vector
	* @param InZ Z vector
	* @param InW W vector
	*/
	Matrix(const Vector& InX, const Vector& InY, const Vector& InZ, const Vector& InW);

	// Set this to the identity matrix
	inline void SetIdentity();

	/**
	* Gets the result of multiplying a Matrix to this.
	*
	* @param Other The matrix to multiply this by.
	* @return The result of multiplication.
	*/
	FORCEINLINE Matrix operator* (const Matrix& Other) const;

	/**
	* Multiply this by a matrix.
	*
	* @param Other the matrix to multiply by this.
	* @return reference to this after multiply.
	*/
	FORCEINLINE void operator*=(const Matrix& Other);

	/**
	* Gets the result of adding a matrix to this.
	*
	* @param Other The Matrix to add.
	* @return The result of addition.
	*/
	FORCEINLINE Matrix operator+ (const Matrix& Other) const;

	/**
	* Adds to this matrix.
	*
	* @param Other The matrix to add to this.
	* @return Reference to this after addition.
	*/
	FORCEINLINE void operator+=(const Matrix& Other);

	/**
	* This isn't applying SCALE, just multiplying float to all members - i.e. weighting
	*/
	FORCEINLINE Matrix operator* (float Other) const;

	/**
	* Multiply this matrix by a weighting factor.
	*
	* @param other The weight.
	* @return a reference to this after weighting.
	*/
	FORCEINLINE void operator*=(float Other);

	/**
	* Checks whether two matrix are identical.
	*
	* @param Other The other matrix.
	* @return true if two matrix are identical, otherwise false.
	*/
	inline bool operator==(const Matrix& Other) const;

	/**
	* Checks whether another Matrix is equal to this, within specified tolerance.
	*
	* @param Other The other Matrix.
	* @param Tolerance Error Tolerance.
	* @return true if two Matrix are equal, within specified tolerance, otherwise false.
	*/
	inline bool Equals(const Matrix& Other, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Checks whether another Matrix is not equal to this, within specified tolerance.
	*
	* @param Other The other Matrix.
	* @return true if two Matrix are not equal, within specified tolerance, otherwise false.
	*/
	inline bool operator!=(const Matrix& Other) const;

	// Homogeneous transform.
	FORCEINLINE Vector4 TransformVector4(const Vector4& V) const;

	/** Transform a location - will take into account translation part of the Matrix. */
	FORCEINLINE Vector4 TransformPosition(const Vector &V) const;

	/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
	FORCEINLINE Vector4 InverseTransformPosition(const Vector &V) const;

	/**
	*	Transform a direction vector - will not take into account translation part of the Matrix.
	*	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
	*/
	FORCEINLINE Vector4 TransformVector(const Vector& V) const;

	/**
	*	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
	*	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
	*/
	FORCEINLINE Vector4 InverseTransformVector(const Vector &V) const;

	// Transpose.

	FORCEINLINE Matrix GetTransposed() const;

	// @return determinant of this matrix.

	inline float Determinant() const;

	/** @return the determinant of rotation 3x3 matrix */
	inline float RotDeterminant() const;

	/** Fast path, doesn't check for nil matrices in final release builds */
	inline Matrix InverseFast() const;

	/** Fast path, and handles nil matrices. */
	inline Matrix Inverse() const;

	inline Matrix TransposeAdjoint() const;

	// NOTE: There is some compiler optimization issues with WIN64 that cause FORCEINLINE to cause a crash
	// Remove any scaling from this matrix (ie magnitude of each row is 1) with error Tolerance
	inline void RemoveScaling(float Tolerance = SMALL_NUMBER);

	// Returns matrix after RemoveScaling with error Tolerance
	inline Matrix GetMatrixWithoutScale(float Tolerance = SMALL_NUMBER) const;

	/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present with error Tolerance */
	inline Vector ExtractScaling(float Tolerance = SMALL_NUMBER);

	/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector) with error Tolerance. */
	inline Vector GetScaleVector(float Tolerance = SMALL_NUMBER) const;

	// Remove any translation from this matrix
	inline Matrix RemoveTranslation() const;

	/** Returns a matrix with an additional translation concatenated. */
	inline Matrix ConcatTranslation(const Vector& Translation) const;

	/** Returns true if any element of this matrix is NaN */
	inline bool ContainsNaN() const;

	/** Scale the translation part of the matrix by the supplied vector. */
	inline void ScaleTranslation(const Vector& Scale3D);

	/** @return the maximum magnitude of any row of the matrix. */
	inline float GetMaximumAxisScale() const;

	/** Apply Scale to this matrix **/
	//inline Matrix ApplyScale(float Scale);

	// @return the origin of the co-ordinate system
	inline Vector GetOrigin() const;
	/**
	* get axis of this matrix scaled by the scale of the matrix
	*
	* @param i index into the axis of the matrix
	* @ return vector of the axis
	*/
	inline Vector GetScaledAxis(EAxis::Type Axis) const;

	/**
	* get axes of this matrix scaled by the scale of the matrix
	*
	* @param X axes returned to this param
	* @param Y axes returned to this param
	* @param Z axes returned to this param
	*/
	inline void GetScaledAxes(Vector &X, Vector &Y, Vector &Z) const;

	/**
	* get unit length axis of this matrix
	*
	* @param i index into the axis of the matrix
	* @return vector of the axis
	*/
	inline Vector GetUnitAxis(EAxis::Type Axis) const;

	/**
	* get unit length axes of this matrix
	*
	* @param X axes returned to this param
	* @param Y axes returned to this param
	* @param Z axes returned to this param
	*/
	inline void GetUnitAxes(Vector &X, Vector &Y, Vector &Z) const;

	/**
	* set an axis of this matrix
	*
	* @param i index into the axis of the matrix
	* @param Axis vector of the axis
	*/
	inline void SetAxis(int32 i, const Vector& Axis);

	// Set the origin of the coordinate system to the given vector
	inline void SetOrigin(const Vector& NewOrigin);

	/**
	* Update the axes of the matrix if any value is NULL do not update that axis
	*
	* @param Axis0 set matrix row 0
	* @param Axis1 set matrix row 1
	* @param Axis2 set matrix row 2
	* @param Origin set matrix row 3
	*/
	inline void SetAxes(Vector* Axis0 = NULL, Vector* Axis1 = NULL, Vector* Axis2 = NULL, Vector* Origin = NULL);


	/**
	* get a column of this matrix
	*
	* @param i index into the column of the matrix
	* @return vector of the column
	*/
	inline Vector GetColumn(int32 i) const;

	/** @return rotator representation of this matrix */
	//FRotator Rotator() const;

	/**
	* Transform a rotation matrix into a quaternion.
	*
	* @warning rotation part will need to be unit length for this to be right!
	*/
	//Quat ToQuat() const;
};


// very high quality 4x4 matrix inverse
static inline void Inverse4x4(double* dst, const float* src)
{
	const double s0 = (double)(src[0]); const double s1 = (double)(src[1]); const double s2 = (double)(src[2]); const double s3 = (double)(src[3]);
	const double s4 = (double)(src[4]); const double s5 = (double)(src[5]); const double s6 = (double)(src[6]); const double s7 = (double)(src[7]);
	const double s8 = (double)(src[8]); const double s9 = (double)(src[9]); const double s10 = (double)(src[10]); const double s11 = (double)(src[11]);
	const double s12 = (double)(src[12]); const double s13 = (double)(src[13]); const double s14 = (double)(src[14]); const double s15 = (double)(src[15]);

	double inv[16];
	inv[0] = s5 * s10 * s15 - s5 * s11 * s14 - s9 * s6 * s15 + s9 * s7 * s14 + s13 * s6 * s11 - s13 * s7 * s10;
	inv[1] = -s1 * s10 * s15 + s1 * s11 * s14 + s9 * s2 * s15 - s9 * s3 * s14 - s13 * s2 * s11 + s13 * s3 * s10;
	inv[2] = s1 * s6  * s15 - s1 * s7  * s14 - s5 * s2 * s15 + s5 * s3 * s14 + s13 * s2 * s7 - s13 * s3 * s6;
	inv[3] = -s1 * s6  * s11 + s1 * s7  * s10 + s5 * s2 * s11 - s5 * s3 * s10 - s9  * s2 * s7 + s9  * s3 * s6;
	inv[4] = -s4 * s10 * s15 + s4 * s11 * s14 + s8 * s6 * s15 - s8 * s7 * s14 - s12 * s6 * s11 + s12 * s7 * s10;
	inv[5] = s0 * s10 * s15 - s0 * s11 * s14 - s8 * s2 * s15 + s8 * s3 * s14 + s12 * s2 * s11 - s12 * s3 * s10;
	inv[6] = -s0 * s6  * s15 + s0 * s7  * s14 + s4 * s2 * s15 - s4 * s3 * s14 - s12 * s2 * s7 + s12 * s3 * s6;
	inv[7] = s0 * s6  * s11 - s0 * s7  * s10 - s4 * s2 * s11 + s4 * s3 * s10 + s8  * s2 * s7 - s8  * s3 * s6;
	inv[8] = s4 * s9  * s15 - s4 * s11 * s13 - s8 * s5 * s15 + s8 * s7 * s13 + s12 * s5 * s11 - s12 * s7 * s9;
	inv[9] = -s0 * s9  * s15 + s0 * s11 * s13 + s8 * s1 * s15 - s8 * s3 * s13 - s12 * s1 * s11 + s12 * s3 * s9;
	inv[10] = s0 * s5  * s15 - s0 * s7  * s13 - s4 * s1 * s15 + s4 * s3 * s13 + s12 * s1 * s7 - s12 * s3 * s5;
	inv[11] = -s0 * s5  * s11 + s0 * s7  * s9 + s4 * s1 * s11 - s4 * s3 * s9 - s8  * s1 * s7 + s8  * s3 * s5;
	inv[12] = -s4 * s9  * s14 + s4 * s10 * s13 + s8 * s5 * s14 - s8 * s6 * s13 - s12 * s5 * s10 + s12 * s6 * s9;
	inv[13] = s0 * s9  * s14 - s0 * s10 * s13 - s8 * s1 * s14 + s8 * s2 * s13 + s12 * s1 * s10 - s12 * s2 * s9;
	inv[14] = -s0 * s5  * s14 + s0 * s6  * s13 + s4 * s1 * s14 - s4 * s2 * s13 - s12 * s1 * s6 + s12 * s2 * s5;
	inv[15] = s0 * s5  * s10 - s0 * s6  * s9 - s4 * s1 * s10 + s4 * s2 * s9 + s8  * s1 * s6 - s8  * s2 * s5;

	double det = s0 * inv[0] + s1 * inv[4] + s2 * inv[8] + s3 * inv[12];
	if (det != 0.0)
	{
		det = 1.0 / det;
	}
	for (int i = 0; i < 16; i++)
	{
		dst[i] = inv[i] * det;
	}
}

FORCEINLINE Matrix::Matrix()
{
}

FORCEINLINE Matrix::Matrix(const Vector& InX, const Vector& InY, const Vector& InZ, const Vector& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = 0.0f;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = 0.0f;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = 0.0f;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = 1.0f;
}


inline void Matrix::SetIdentity()
{
	M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
	M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
	M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
	M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;
}


FORCEINLINE void Matrix::operator*=(const Matrix& Other)
{
	VectorMatrixMultiply(this, this, &Other);
}


FORCEINLINE Matrix Matrix::operator*(const Matrix& Other) const
{
	Matrix Result;
	VectorMatrixMultiply(&Result, this, &Other);
	return Result;
}


FORCEINLINE Matrix	Matrix::operator+(const Matrix& Other) const
{
	Matrix ResultMat;

	for (int32 X = 0; X < 4; X++)
	{
		for (int32 Y = 0; Y < 4; Y++)
		{
			ResultMat.M[X][Y] = M[X][Y] + Other.M[X][Y];
		}
	}

	return ResultMat;
}

FORCEINLINE void Matrix::operator+=(const Matrix& Other)
{
	*this = *this + Other;
}

FORCEINLINE Matrix	Matrix::operator*(float Other) const
{
	Matrix ResultMat;

	for (int32 X = 0; X < 4; X++)
	{
		for (int32 Y = 0; Y < 4; Y++)
		{
			ResultMat.M[X][Y] = M[X][Y] * Other;
		}
	}

	return ResultMat;
}

FORCEINLINE void Matrix::operator*=(float Other)
{
	*this = *this*Other;
}

// Comparison operators.

inline bool Matrix::operator==(const Matrix& Other) const
{
	for (int32 X = 0; X < 4; X++)
	{
		for (int32 Y = 0; Y < 4; Y++)
		{
			if (M[X][Y] != Other.M[X][Y])
			{
				return false;
			}
		}
	}

	return true;
}

// Error-tolerant comparison.
inline bool Matrix::Equals(const Matrix& Other, float Tolerance/*=KINDA_SMALL_NUMBER*/) const
{
	for (int32 X = 0; X < 4; X++)
	{
		for (int32 Y = 0; Y < 4; Y++)
		{
			if (Math::Abs(M[X][Y] - Other.M[X][Y]) > Tolerance)
			{
				return false;
			}
		}
	}

	return true;
}

inline bool Matrix::operator!=(const Matrix& Other) const
{
	return !(*this == Other);
}


// Homogeneous transform.

FORCEINLINE Vector4 Matrix::TransformVector4(const Vector4 &P) const
{
	Vector4 Result;
	VectorRegister VecP = VectorLoadAligned(&P);
	VectorRegister VecR = VectorTransformVector(VecP, this);
	VectorStoreAligned(VecR, &Result);
	return Result;
}


// Transform position

/** Transform a location - will take into account translation part of the Matrix. */
FORCEINLINE Vector4 Matrix::TransformPosition(const Vector &V) const
{
	return TransformVector4(Vector4(V.X, V.Y, V.Z, 1.0f));
}

/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
FORCEINLINE Vector4 Matrix::InverseTransformPosition(const Vector &V) const
{
	Matrix InvSelf = this->InverseFast();
	return InvSelf.TransformPosition(V);
}

// Transform vector

/**
*	Transform a direction vector - will not take into account translation part of the Matrix.
*	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
*/
FORCEINLINE Vector4 Matrix::TransformVector(const Vector& V) const
{
	return TransformVector4(Vector4(V.X, V.Y, V.Z, 0.0f));
}

/** Faster version of InverseTransformVector that assumes no scaling. WARNING: Will NOT work correctly if there is scaling in the matrix. */
FORCEINLINE Vector4 Matrix::InverseTransformVector(const Vector &V) const
{
	Matrix InvSelf = this->InverseFast();
	return InvSelf.TransformVector(V);
}


// Transpose.

FORCEINLINE Matrix Matrix::GetTransposed() const
{
	Matrix	Result;

	Result.M[0][0] = M[0][0];
	Result.M[0][1] = M[1][0];
	Result.M[0][2] = M[2][0];
	Result.M[0][3] = M[3][0];

	Result.M[1][0] = M[0][1];
	Result.M[1][1] = M[1][1];
	Result.M[1][2] = M[2][1];
	Result.M[1][3] = M[3][1];

	Result.M[2][0] = M[0][2];
	Result.M[2][1] = M[1][2];
	Result.M[2][2] = M[2][2];
	Result.M[2][3] = M[3][2];

	Result.M[3][0] = M[0][3];
	Result.M[3][1] = M[1][3];
	Result.M[3][2] = M[2][3];
	Result.M[3][3] = M[3][3];

	return Result;
}

// Determinant.

inline float Matrix::Determinant() const
{
	return	M[0][0] * (
		M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
		M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
		M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
		) -
		M[1][0] * (
		M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
		M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
		M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
		) +
		M[2][0] * (
		M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
		M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
		M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
		) -
		M[3][0] * (
		M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
		M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
		M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
		);
}

/** Calculate determinant of rotation 3x3 matrix */
inline float Matrix::RotDeterminant() const
{
	return
		M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
		M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
		M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
}

// Inverse.
/** Fast path, doesn't check for nil matrices in final release builds */
inline Matrix Matrix::InverseFast() const
{
	// If we're in non final release, then make sure we're not creating NaNs
#ifdef DEBUG_MODE	
	// Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(SMALL_NUMBER) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(SMALL_NUMBER) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(SMALL_NUMBER))
	{
		DEBUG_MESSAGE(RAY_ERROR, "Matrix::Inverse(), trying to invert a NIL matrix, this results in NaNs! Use Inverse() instead.");
	}
#endif
	Matrix Result;
	VectorMatrixInverse(&Result, this);
	return Result;
}

// Inverse.
inline Matrix Matrix::Inverse() const
{
	Matrix Result;

	// Check for zero scale matrix to invert
	if (GetScaledAxis(EAxis::X).IsNearlyZero(SMALL_NUMBER) &&
		GetScaledAxis(EAxis::Y).IsNearlyZero(SMALL_NUMBER) &&
		GetScaledAxis(EAxis::Z).IsNearlyZero(SMALL_NUMBER))
	{
		// just set to zero - avoids unsafe inverse of zero and duplicates what QNANs were resulting in before (scaling away all children)
		Result = Matrix::Identity;
	}
	else
	{
		const float	Det = Determinant();

		if (Det == 0.0f)
		{
			Result = Matrix::Identity;
		}
		else
		{
			VectorMatrixInverse(&Result, this);
		}
	}

	return Result;
}

inline Matrix Matrix::TransposeAdjoint() const
{
	Matrix TA;

	TA.M[0][0] = this->M[1][1] * this->M[2][2] - this->M[1][2] * this->M[2][1];
	TA.M[0][1] = this->M[1][2] * this->M[2][0] - this->M[1][0] * this->M[2][2];
	TA.M[0][2] = this->M[1][0] * this->M[2][1] - this->M[1][1] * this->M[2][0];
	TA.M[0][3] = 0.f;

	TA.M[1][0] = this->M[2][1] * this->M[0][2] - this->M[2][2] * this->M[0][1];
	TA.M[1][1] = this->M[2][2] * this->M[0][0] - this->M[2][0] * this->M[0][2];
	TA.M[1][2] = this->M[2][0] * this->M[0][1] - this->M[2][1] * this->M[0][0];
	TA.M[1][3] = 0.f;

	TA.M[2][0] = this->M[0][1] * this->M[1][2] - this->M[0][2] * this->M[1][1];
	TA.M[2][1] = this->M[0][2] * this->M[1][0] - this->M[0][0] * this->M[1][2];
	TA.M[2][2] = this->M[0][0] * this->M[1][1] - this->M[0][1] * this->M[1][0];
	TA.M[2][3] = 0.f;

	TA.M[3][0] = 0.f;
	TA.M[3][1] = 0.f;
	TA.M[3][2] = 0.f;
	TA.M[3][3] = 1.f;

	return TA;
}

// NOTE: There is some compiler optimization issues with WIN64 that cause FORCEINLINE to cause a crash
// Remove any scaling from this matrix (ie magnitude of each row is 1)
inline void Matrix::RemoveScaling(float Tolerance/*=SMALL_NUMBER*/)
{
	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const float SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const float SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const float SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);
	const float Scale0 = Math::FloatSelect(SquareSum0 - Tolerance, Math::InvSqrt(SquareSum0), 1.0f);
	const float Scale1 = Math::FloatSelect(SquareSum1 - Tolerance, Math::InvSqrt(SquareSum1), 1.0f);
	const float Scale2 = Math::FloatSelect(SquareSum2 - Tolerance, Math::InvSqrt(SquareSum2), 1.0f);
	M[0][0] *= Scale0;
	M[0][1] *= Scale0;
	M[0][2] *= Scale0;
	M[1][0] *= Scale1;
	M[1][1] *= Scale1;
	M[1][2] *= Scale1;
	M[2][0] *= Scale2;
	M[2][1] *= Scale2;
	M[2][2] *= Scale2;
}

// Returns matrix without scale information
inline Matrix Matrix::GetMatrixWithoutScale(float Tolerance/*=SMALL_NUMBER*/) const
{
	Matrix Result = *this;
	Result.RemoveScaling(Tolerance);
	return Result;
}

/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present. */
inline Vector Matrix::ExtractScaling(float Tolerance/*=SMALL_NUMBER*/)
{
	Vector Scale3D(0, 0, 0);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const float SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const float SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const float SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

	if (SquareSum0 > Tolerance)
	{
		float Scale0 = Math::Sqrt(SquareSum0);
		Scale3D[0] = Scale0;
		float InvScale0 = 1.f / Scale0;
		M[0][0] *= InvScale0;
		M[0][1] *= InvScale0;
		M[0][2] *= InvScale0;
	}
	else
	{
		Scale3D[0] = 0;
	}

	if (SquareSum1 > Tolerance)
	{
		float Scale1 = Math::Sqrt(SquareSum1);
		Scale3D[1] = Scale1;
		float InvScale1 = 1.f / Scale1;
		M[1][0] *= InvScale1;
		M[1][1] *= InvScale1;
		M[1][2] *= InvScale1;
	}
	else
	{
		Scale3D[1] = 0;
	}

	if (SquareSum2 > Tolerance)
	{
		float Scale2 = Math::Sqrt(SquareSum2);
		Scale3D[2] = Scale2;
		float InvScale2 = 1.f / Scale2;
		M[2][0] *= InvScale2;
		M[2][1] *= InvScale2;
		M[2][2] *= InvScale2;
	}
	else
	{
		Scale3D[2] = 0;
	}

	return Scale3D;
}

/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector). */
inline Vector Matrix::GetScaleVector(float Tolerance/*=SMALL_NUMBER*/) const
{
	Vector Scale3D(1, 1, 1);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	for (int32 i = 0; i<3; i++)
	{
		const float SquareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
		if (SquareSum > Tolerance)
		{
			Scale3D[i] = Math::Sqrt(SquareSum);
		}
		else
		{
			Scale3D[i] = 0.f;
		}
	}

	return Scale3D;
}
// Remove any translation from this matrix
inline Matrix Matrix::RemoveTranslation() const
{
	Matrix Result = *this;
	Result.M[3][0] = 0.0f;
	Result.M[3][1] = 0.0f;
	Result.M[3][2] = 0.0f;
	return Result;
}

FORCEINLINE Matrix Matrix::ConcatTranslation(const Vector& Translation) const
{
	Matrix Result;

	float* Dest = &Result.M[0][0];
	const float* Src = &M[0][0];
	const float* Trans = &Translation.X;

	Dest[0] = Src[0];
	Dest[1] = Src[1];
	Dest[2] = Src[2];
	Dest[3] = Src[3];
	Dest[4] = Src[4];
	Dest[5] = Src[5];
	Dest[6] = Src[6];
	Dest[7] = Src[7];
	Dest[8] = Src[8];
	Dest[9] = Src[9];
	Dest[10] = Src[10];
	Dest[11] = Src[11];
	Dest[12] = Src[12] + Trans[0];
	Dest[13] = Src[13] + Trans[1];
	Dest[14] = Src[14] + Trans[2];
	Dest[15] = Src[15];

	return Result;
}

/** Returns true if any element of this matrix is NaN */
inline bool Matrix::ContainsNaN() const
{
	for (int32 i = 0; i<4; i++)
	{
		for (int32 j = 0; j<4; j++)
		{
			if (Math::IsNaN(M[i][j]) || !Math::IsFinite(M[i][j]))
			{
				return true;
			}
		}
	}

	return false;
}

/** @return the maximum magnitude of any row of the matrix. */
inline float Matrix::GetMaximumAxisScale() const
{
	const float MaxRowScaleSquared = Math::Max(
		GetScaledAxis(EAxis::X).SizeSquared(),
		Math::Max(
		GetScaledAxis(EAxis::Y).SizeSquared(),
		GetScaledAxis(EAxis::Z).SizeSquared()
		)
		);
	return Math::Sqrt(MaxRowScaleSquared);
}

inline void Matrix::ScaleTranslation(const Vector& Scale3D)
{
	M[3][0] *= Scale3D.X;
	M[3][1] *= Scale3D.Y;
	M[3][2] *= Scale3D.Z;
}

// GetOrigin

inline Vector Matrix::GetOrigin() const
{
	return Vector(M[3][0], M[3][1], M[3][2]);
}

/**
* Apply Scale to this matrix
*/
//inline Matrix Matrix::ApplyScale(float Scale)
//{
//	return ScaleMatrix(Scale)*(*this);
//}

struct LookAtMatrix : Matrix
{
	/**
	* Creates a view matrix given an eye position, a position to look at, and an up vector.
	* This does the same thing as D3DXMatrixLookAtRH.
	*/
	LookAtMatrix(const Vector& EyePosition, const Vector& LookAtPosition, const Vector& UpVector);
};

FORCEINLINE LookAtMatrix::LookAtMatrix(const Vector& EyePosition, const Vector& LookAtPosition, const Vector& UpVector)
{
	const Vector ZAxis = (EyePosition-LookAtPosition).GetSafeNormal();
	const Vector XAxis = (UpVector^ZAxis).GetSafeNormal();
	const Vector YAxis = ZAxis^XAxis;

	for (uint16 rowIndex = 0; rowIndex < 3; ++rowIndex)
	{
		M[rowIndex][0] = (&XAxis.X)[rowIndex];
		M[rowIndex][1] = (&YAxis.X)[rowIndex];
		M[rowIndex][2] = (&ZAxis.X)[rowIndex];
		M[rowIndex][3] = 0.0f;
	}

	M[3][0] = -EyePosition | XAxis;
	M[3][1] = -EyePosition | YAxis;
	M[3][2] = -EyePosition | ZAxis;
	M[3][3] = 1.0f;
}

struct PerspectiveProjectMatrix : Matrix
{
	/**
	* Creates a perspective projection matrix given a ratio, a fove, a near and far plane.
	* This does the same thing as D3DXMatrixPerspectiveRH.
	*/
	PerspectiveProjectMatrix(float ratio, float fov, float far, float near);
};

FORCEINLINE  PerspectiveProjectMatrix::PerspectiveProjectMatrix(float ratio, float fov, float near, float far)
{
	const float range = far-near;
	const float tanHalfFOV = Math::Tan(Math::DegreesToRadians(fov / 2.0f));

	M[0][0] = 1.0f / (tanHalfFOV * ratio);	M[0][1] = 0.0f;				 M[0][2] = 0.0f;				   M[0][3] = 0.0f;
	M[1][0] = 0.0f;							M[1][1] = 1.0f / tanHalfFOV; M[1][2] = 0.0f;				   M[1][3] = 0.0f;
	M[2][0] = 0.0f;							M[2][1] = 0.0f;				 M[2][2] = (near + far) / range;   M[2][3] = -1.0f;
	M[3][0] = 0.0f;							M[3][1] = 0.0f;				 M[3][2] = 2.0f*far*near / range;  M[3][3] = 0.0f;
}
