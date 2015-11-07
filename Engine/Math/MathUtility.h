//===========================================================================
// MathUtility: Math Utilitys for code
//===========================================================================

#pragma once

/*-----------------------------------------------------------------------------
Definitions.
-----------------------------------------------------------------------------*/
#include "../Config/RayConifg.h"
#include "../Config/WindowPlatform.h"
#include "NumbericLimits.h"

#include <math.h>
#include <stdlib.h>

// Forward declarations.
struct  Vector;
struct  Vector4;
//struct  Plane;
//struct  Box;
struct  Rotator;
struct  Matrix;
struct  Quaternion;
//struct  TwoVectors;
//struct  Transform;
//class  Sphere;
//struct Vector2D;
//struct LinearColor;

/*-----------------------------------------------------------------------------
Floating point constants.
-----------------------------------------------------------------------------*/

#undef  PI
#define PI 					(3.1415926535897932f)
#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)
#define BIG_NUMBER			(3.4e+38f)
#define EULERS_NUMBER       (2.71828182845904523536f)

// Copied from float.h
#define MAX_FLT 3.402823466e+38F

// Aux constants.
#define INV_PI			(0.31830988618f)
#define HALF_PI			(1.57079632679f)

// Magic numbers for numerical precision.
#define DELTA			(0.00001f)

//
// Magic numbers for numerical precision.
//
#define THRESH_POINT_ON_PLANE			(0.10f)		/* Thickness of plane for front/back/inside test */
#define THRESH_POINT_ON_SIDE			(0.20f)		/* Thickness of polygon side's side-plane for point-inside/outside/on side test */
#define THRESH_POINTS_ARE_SAME			(0.00002f)	/* Two points are same if within this distance */
#define THRESH_POINTS_ARE_NEAR			(0.015f)	/* Two points are near if within this distance and can be combined if imprecise math is ok */
#define THRESH_NORMALS_ARE_SAME			(0.00002f)	/* Two normal points are same if within this distance */
/* Making this too large results in incorrect CSG classification and disaster */
#define THRESH_VECTORS_ARE_NEAR			(0.0004f)	/* Two vectors are near if within this distance and can be combined if imprecise math is ok */
/* Making this too large results in lighting problems due to inaccurate texture coordinates */
#define THRESH_SPLIT_POLY_WITH_PLANE	(0.25f)		/* A plane splits a polygon in half */
#define THRESH_SPLIT_POLY_PRECISELY		(0.01f)		/* A plane exactly splits a polygon */
#define THRESH_ZERO_NORM_SQUARED		(0.0001f)	/* Size of a unit normal that is considered "zero", squared */
#define THRESH_NORMALS_ARE_PARALLEL		(0.999845f)	/* Two unit vectors are parallel if abs(A dot B) is greater than or equal to this. This is roughly cosine(1.0 degrees). */
#define THRESH_NORMALS_ARE_ORTHOGONAL	(0.017455f)	/* Two unit vectors are orthogonal (perpendicular) if abs(A dot B) is less than or equal this. This is roughly cosine(89.0 degrees). */

#define THRESH_VECTOR_NORMALIZED		(0.01f)		/** Allowed error for a normalized vector (against squared magnitude) */
#define THRESH_QUAT_NORMALIZED			(0.01f)		/** Allowed error for a normalized quaternion (against squared magnitude) */


struct Math
{
	/**
	* Converts a float to an integer with truncation towards zero.
	* @param F		Floating point value to convert
	* @return		Truncated integer.
	*/
	static FORCEINLINE int32 TruncToInt(float F)
	{
		return (int32)(F);
	}

	/**
	* Converts a float to an integer value with truncation towards zero.
	* @param F		Floating point value to convert
	* @return		Truncated integer value.
	*/
	static FORCEINLINE float TruncToFloat(float F)
	{
		return (float)TruncToInt(F);
	}

	/**
	* Converts a float to a nearest less or equal integer.
	* @param F		Floating point value to convert
	* @return		An integer less or equal to 'F'.
	*/
	static FORCEINLINE int32 FloorToInt(float F)
	{
		return TruncToInt(floorf(F));
	}

	/**
	* Converts a float to the nearest less or equal integer.
	* @param F		Floating point value to convert
	* @return		An integer less or equal to 'F'.
	*/
	static FORCEINLINE float FloorToFloat(float F)
	{
		return floorf(F);
	}

	/**
	* Converts a double to a less or equal integer.
	* @param F		Floating point value to convert
	* @return		The nearest integer value to 'F'.
	*/
	static FORCEINLINE double FloorToDouble(double F)
	{
		return floor(F);
	}

	/**
	* Converts a float to the nearest integer. Rounds up when the fraction is .5
	* @param F		Floating point value to convert
	* @return		The nearest integer to 'F'.
	*/
	static FORCEINLINE int32 RoundToInt(float F)
	{
		return FloorToInt(F + 0.5f);
	}

	/**
	* Converts a float to the nearest integer. Rounds up when the fraction is .5
	* @param F		Floating point value to convert
	* @return		The nearest integer to 'F'.
	*/
	static FORCEINLINE float RoundToFloat(float F)
	{
		return FloorToFloat(F + 0.5f);
	}

	/**
	* Converts a float to the nearest greater or equal integer.
	* @param F		Floating point value to convert
	* @return		An integer greater or equal to 'F'.
	*/
	static FORCEINLINE int32 CeilToInt(float F)
	{
		return TruncToInt(ceilf(F));
	}

	/**
	* Converts a float to the nearest greater or equal integer.
	* @param F		Floating point value to convert
	* @return		An integer greater or equal to 'F'.
	*/
	static FORCEINLINE float CeilToFloat(float F)
	{
		return ceilf(F);
	}

	/**
	* Returns signed fractional part of a float.
	* @param Value	Floating point value to convert
	* @return		A float between >=0 and < 1 for nonnegative input. A float between >= -1 and < 0 for negative input.
	*/
	static FORCEINLINE float Fractional(float Value)
	{
		return Value - TruncToFloat(Value);
	}

	/**
	* Returns the fractional part of a float.
	* @param Value	Floating point value to convert
	* @return		A float between >=0 and < 1.
	*/
	static FORCEINLINE float Frac(float Value)
	{
		return Value - FloorToFloat(Value);
	}

	static FORCEINLINE float Exp(float Value) { return expf(Value); }
	static FORCEINLINE float Loge(float Value) { return logf(Value); }
	static FORCEINLINE float LogX(float Base, float Value) { return Loge(Value) / Loge(Base); }
	// 1.0 / Loge(2) = 1.4426950f
	static FORCEINLINE float Log2(float Value) { return Loge(Value) * 1.4426950f; }

	/**
	* Returns the floating-point remainder of X / Y
	* Warning: Always returns remainder toward 0, not toward the smaller multiple of Y.
	*			So for example Fmod(2.8f, 2) gives .8f as you would expect, however, Fmod(-2.8f, 2) gives -.8f, NOT 1.2f
	* Use Floor instead when snapping positions that can be negative to a grid
	*/
	static FORCEINLINE float Fmod(float X, float Y) { return fmodf(X, Y); }
	static FORCEINLINE float Sin(float Value) { return sinf(Value); }
	static FORCEINLINE float Asin(float Value) { return asinf((Value<-1.f) ? -1.f : ((Value<1.f) ? Value : 1.f)); }
	static FORCEINLINE float Cos(float Value) { return cosf(Value); }
	static FORCEINLINE float Acos(float Value) { return acosf((Value<-1.f) ? -1.f : ((Value<1.f) ? Value : 1.f)); }
	static FORCEINLINE float Tan(float Value) { return tanf(Value); }
	static FORCEINLINE float Atan(float Value) { return atanf(Value); }
	static FORCEINLINE float Atan2(float Y, float X) { return atan2f(Y, X); }
	static FORCEINLINE float Sqrt(float Value) { return sqrtf(Value); }
	static FORCEINLINE float Pow(float A, float B) { return powf(A, B); }

	/** Computes a fully accurate inverse square root */
	static FORCEINLINE float InvSqrt(float F)
	{
		return 1.0f / sqrtf(F);
	}

	/** Computes a faster but less accurate inverse square root */
	static FORCEINLINE float InvSqrtEst(float F)
	{
		return InvSqrt(F);
	}

	static FORCEINLINE bool IsNaN(float A)
	{
		return ((*(uint32*)&A) & 0x7FFFFFFF) > 0x7F800000;
	}
	static FORCEINLINE bool IsFinite(float A)
	{
		return ((*(uint32*)&A) & 0x7F800000) != 0x7F800000;
	}
	static FORCEINLINE bool IsNegativeFloat(const float& F1)
	{
		return ((*(uint32*)&F1) >= (uint32)0x80000000); // Detects sign bit.
	}

	/** Returns a random integer between 0 and RAND_MAX, inclusive */
	static FORCEINLINE int32 Rand() { return rand(); }

	/** Seeds global random number functions Rand() and FRand() */
	static FORCEINLINE void RandInit(int32 Seed) { srand(Seed); }

	/** Returns a random float between 0 and 1, inclusive. */
	static FORCEINLINE float FRand() { return Rand() / (float)RAND_MAX; }

	/** Seeds future calls to SRand() */
	static void SRandInit(int32 Seed);

	/** Returns the current seed for SRand(). */
	static int32 GetRandSeed();

	/** Returns a seeded random float in the range [0,1), using the seed from SRandInit(). */
	static float SRand();

	/**
	* Computes the base 2 logarithm for an integer value that is greater than 0.
	* The result is rounded down to the nearest integer.
	*
	* @param Value		The value to compute the log of
	* @return			Log2 of Value. 0 if Value is 0.
	*/
	static FORCEINLINE uint32 FloorLog2(uint32 Value)
	{
		/*		// reference implementation
		// 1500ms on test data
		uint32 Bit = 32;
		for (; Bit > 0;)
		{
		Bit--;
		if (Value & (1<<Bit))
		{
		break;
		}
		}
		return Bit;
		*/
		// same output as reference

		// see http://codinggorilla.domemtech.com/?p=81 or http://en.wikipedia.org/wiki/Binary_logarithm but modified to return 0 for a input value of 0
		// 686ms on test data
		uint32 pos = 0;
		if (Value >= 1 << 16) { Value >>= 16; pos += 16; }
		if (Value >= 1 << 8) { Value >>= 8; pos += 8; }
		if (Value >= 1 << 4) { Value >>= 4; pos += 4; }
		if (Value >= 1 << 2) { Value >>= 2; pos += 2; }
		if (Value >= 1 << 1) { pos += 1; }
		return (Value == 0) ? 0 : pos;

		// even faster would be method3 but it can introduce more cache misses and it would need to store the table somewhere
		// 304ms in test data
		/*int LogTable256[256];

		void prep()
		{
		LogTable256[0] = LogTable256[1] = 0;
		for (int i = 2; i < 256; i++)
		{
		LogTable256[i] = 1 + LogTable256[i / 2];
		}
		LogTable256[0] = -1; // if you want log(0) to return -1
		}

		int _forceinline method3(uint32 v)
		{
		int r;     // r will be lg(v)
		uint32 tt; // temporaries

		if ((tt = v >> 24) != 0)
		{
		r = (24 + LogTable256[tt]);
		}
		else if ((tt = v >> 16) != 0)
		{
		r = (16 + LogTable256[tt]);
		}
		else if ((tt = v >> 8 ) != 0)
		{
		r = (8 + LogTable256[tt]);
		}
		else
		{
		r = LogTable256[v];
		}
		return r;
		}*/
	}

	/**
	* Counts the number of leading zeros in the bit representation of the value
	*
	* @param Value the value to determine the number of leading zeros for
	*
	* @return the number of zeros before the first "on" bit
	*/
	static FORCEINLINE uint32 CountLeadingZeros(uint32 Value)
	{
		if (Value == 0) return 32;
		return 31 - FloorLog2(Value);
	}

	/**
	* Returns smallest N such that (1<<N)>=Arg.
	* Note: CeilLogTwo(0)=0 because (1<<0)=1 >= 0.
	*/
	static FORCEINLINE uint32 CeilLogTwo(uint32 Arg)
	{
		int32 Bitmask = ((int32)(CountLeadingZeros(Arg) << 26)) >> 31;
		return (32 - CountLeadingZeros(Arg - 1)) & (~Bitmask);
	}

	/** @return Rounds the given number up to the next highest power of two. */
	static FORCEINLINE uint32 RoundUpToPowerOfTwo(uint32 Arg)
	{
		return 1 << CeilLogTwo(Arg);
	}

	/** Spreads bits to every other. */
	static FORCEINLINE uint32 MortonCode2(uint32 x)
	{
		x &= 0x0000ffff;
		x = (x ^ (x << 8)) & 0x00ff00ff;
		x = (x ^ (x << 4)) & 0x0f0f0f0f;
		x = (x ^ (x << 2)) & 0x33333333;
		x = (x ^ (x << 1)) & 0x55555555;
		return x;
	}

	/** Reverses MortonCode2. Compacts every other bit to the right. */
	static FORCEINLINE uint32 ReverseMortonCode2(uint32 x)
	{
		x &= 0x55555555;
		x = (x ^ (x >> 1)) & 0x33333333;
		x = (x ^ (x >> 2)) & 0x0f0f0f0f;
		x = (x ^ (x >> 4)) & 0x00ff00ff;
		x = (x ^ (x >> 8)) & 0x0000ffff;
		return x;
	}

	/** Spreads bits to every 3rd. */
	static FORCEINLINE uint32 MortonCode3(uint32 x)
	{
		x &= 0x000003ff;
		x = (x ^ (x << 16)) & 0xff0000ff;
		x = (x ^ (x << 8)) & 0x0300f00f;
		x = (x ^ (x << 4)) & 0x030c30c3;
		x = (x ^ (x << 2)) & 0x09249249;
		return x;
	}

	/** Reverses MortonCode3. Compacts every 3rd bit to the right. */
	static FORCEINLINE uint32 ReverseMortonCode3(uint32 x)
	{
		x &= 0x09249249;
		x = (x ^ (x >> 2)) & 0x030c30c3;
		x = (x ^ (x >> 4)) & 0x0300f00f;
		x = (x ^ (x >> 8)) & 0xff0000ff;
		x = (x ^ (x >> 16)) & 0x000003ff;
		return x;
	}

	/**
	* Returns value based on comparand. The main purpose of this function is to avoid
	* branching based on floating point comparison which can be avoided via compiler
	* intrinsics.
	*
	* Please note that we don't define what happens in the case of NaNs as there might
	* be platform specific differences.
	*
	* @param	Comparand		Comparand the results are based on
	* @param	ValueGEZero		Return value if Comparand >= 0
	* @param	ValueLTZero		Return value if Comparand < 0
	*
	* @return	ValueGEZero if Comparand >= 0, ValueLTZero otherwise
	*/
	static FORCEINLINE float FloatSelect(float Comparand, float ValueGEZero, float ValueLTZero)
	{
		return Comparand >= 0.f ? ValueGEZero : ValueLTZero;
	}

	/**
	* Returns value based on comparand. The main purpose of this function is to avoid
	* branching based on floating point comparison which can be avoided via compiler
	* intrinsics.
	*
	* Please note that we don't define what happens in the case of NaNs as there might
	* be platform specific differences.
	*
	* @param	Comparand		Comparand the results are based on
	* @param	ValueGEZero		Return value if Comparand >= 0
	* @param	ValueLTZero		Return value if Comparand < 0
	*
	* @return	ValueGEZero if Comparand >= 0, ValueLTZero otherwise
	*/
	static FORCEINLINE double FloatSelect(double Comparand, double ValueGEZero, double ValueLTZero)
	{
		return Comparand >= 0.f ? ValueGEZero : ValueLTZero;
	}

	/** Computes absolute value in a generic way */
	template< class T >
	static FORCEINLINE T Abs(const T A)
	{
		return (A >= (T)0) ? A : -A;
	}

	/** Returns 1, 0, or -1 depending on relation of T to 0 */
	template< class T >
	static FORCEINLINE T Sign(const T A)
	{
		return (A > (T)0) ? (T)1 : ((A < (T)0) ? (T)-1 : (T)0);
	}

	/** Returns higher value in a generic way */
	template< class T >
	static FORCEINLINE T Max(const T A, const T B)
	{
		return (A >= B) ? A : B;
	}

	/** Returns lower value in a generic way */
	template< class T >
	static FORCEINLINE T Min(const T A, const T B)
	{
		return (A <= B) ? A : B;
	}

	///**
	//* Min of Array
	//* @param	Array of templated type
	//* @param	Optional pointer for returning the index of the minimum element, if multiple minimum elements the first index is returned
	//* @return	The min value found in the array or default value if the array was empty
	//*/
	//template< class T >
	//static FORCEINLINE T Min(const TArray<T>& Values, int32* MinIndex = NULL)
	//{
	//	if (Values.Num() == 0)
	//	{
	//		if (MinIndex)
	//		{
	//			*MinIndex = INDEX_NONE;
	//		}
	//		return T();
	//	}

	//	T CurMin = Values[0];
	//	int32 CurMinIndex = 0;
	//	for (int32 v = 1; v < Values.Num(); ++v)
	//	{
	//		const T Value = Values[v];
	//		if (Value < CurMin)
	//		{
	//			CurMin = Value;
	//			CurMinIndex = v;
	//		}
	//	}

	//	if (MinIndex)
	//	{
	//		*MinIndex = CurMinIndex;
	//	}
	//	return CurMin;
	//}

	///**
	//* Max of Array
	//* @param	Array of templated type
	//* @param	Optional pointer for returning the index of the maximum element, if multiple maximum elements the first index is returned
	//* @return	The max value found in the array or default value if the array was empty
	//*/
	//template< class T >
	//static FORCEINLINE T Max(const TArray<T>& Values, int32* MaxIndex = NULL)
	//{
	//	if (Values.Num() == 0)
	//	{
	//		if (MaxIndex)
	//		{
	//			*MaxIndex = INDEX_NONE;
	//		}
	//		return T();
	//	}

	//	T CurMax = Values[0];
	//	int32 CurMaxIndex = 0;
	//	for (int32 v = 1; v < Values.Num(); ++v)
	//	{
	//		const T Value = Values[v];
	//		if (CurMax < Value)
	//		{
	//			CurMax = Value;
	//			CurMaxIndex = v;
	//		}
	//	}

	//	if (MaxIndex)
	//	{
	//		*MaxIndex = CurMaxIndex;
	//	}
	//	return CurMax;
	//}

	/** Test some of the tricky functions above **/
	static void AutoTest();
	
	// Random Number Functions________________________________________________________________________________

	/** Helper function for rand implementations. Returns a random number in [0..A) */
	static FORCEINLINE int32 RandHelper(int32 A)
	{
		// RAND_MAX+1 give interval [0..A) with even distribution.
		return A>0 ? TruncToInt(Rand() / (float)((uint32)RAND_MAX + 1) * A) : 0;
	}

	/** Helper function for rand implementations. Returns a random number >= Min and <= Max */
	static FORCEINLINE int32 RandRange(int32 Min, int32 Max)
	{
		const int32 Range = (Max - Min) + 1;
		return Min + RandHelper(Range);
	}

	/** Util to generate a random number in a range. */
	static FORCEINLINE float FRandRange(float InMin, float InMax)
	{
		return InMin + (InMax - InMin) * FRand();
	}

	/** Return a uniformly distributed random unit length vector = point on the unit sphere surface. */
	static Vector VRand();

	/**
	* Returns a random unit vector, uniformly distributed, within the specified cone
	* ConeHalfAngleRad is the half-angle of cone, in radians.  Returns a normalized vector.
	*/
	static Vector VRandCone(Vector const& Dir, float ConeHalfAngleRad);

	/**
	* This is a version of VRandCone that handles "squished" cones, i.e. with different angle limits in the Y and Z axes.
	* Assumes world Y and Z, although this could be extended to handle arbitrary rotations.
	*/
	static Vector VRandCone(Vector const& Dir, float HorizontalConeHalfAngleRad, float VerticalConeHalfAngleRad);

	/** Returns a random point within the passed in bounding box */
	//static Vector RandPointInBox(const Box& Box);

	/**
	* Given a direction vector and a surface normal, returns the vector reflected across the surface normal.
	* Produces a result like shining a laser at a mirror!
	*
	* @param Direction Direction vector the ray is comming from.
	* @param SurfaceNormal A normal of the surface the ray should be reflected on.
	*
	* @returns Reflected vector.
	*/
	static Vector GetReflectionVector(const Vector& Direction, const Vector& SurfaceNormal);

	// Predicates

	/** Checks if value is within a range, exclusive on MaxValue) */
	template< class U >
	static FORCEINLINE bool IsWithin(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue >= MinValue) && (TestValue < MaxValue));
	}

	/** Checks if value is within a range, inclusive on MaxValue) */
	template< class U >
	static FORCEINLINE bool IsWithinInclusive(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue >= MinValue) && (TestValue <= MaxValue));
	}

	/**
	*	Checks if two floating point numbers are nearly equal.
	*	@param A				First number to compare
	*	@param B				Second number to compare
	*	@param ErrorTolerance	Maximum allowed difference for considering them as 'nearly equal'
	*	@return					true if A and B are nearly equal
	*/
	static FORCEINLINE bool IsNearlyEqual(float A, float B, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>(A - B) < ErrorTolerance;
	}

	/**
	*	Checks if two floating point numbers are nearly equal.
	*	@param A				First number to compare
	*	@param B				Second number to compare
	*	@param ErrorTolerance	Maximum allowed difference for considering them as 'nearly equal'
	*	@return					true if A and B are nearly equal
	*/
	static FORCEINLINE bool IsNearlyEqual(double A, double B, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>(A - B) < ErrorTolerance;
	}

	/**
	*	Checks if a floating point number is nearly zero.
	*	@param Value			Number to compare
	*	@param ErrorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
	*	@return					true if Value is nearly zero
	*/
	static FORCEINLINE bool IsNearlyZero(float Value, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>(Value) < ErrorTolerance;
	}

	/**
	*	Checks if a floating point number is nearly zero.
	*	@param Value			Number to compare
	*	@param ErrorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
	*	@return					true if Value is nearly zero
	*/
	static FORCEINLINE bool IsNearlyZero(double Value, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>(Value) < ErrorTolerance;
	}

	/**
	*	Checks whether a number is a power of two.
	*	@param Value	Number to check
	*	@return			true if Value is a power of two
	*/
	static FORCEINLINE bool IsPowerOfTwo(uint32 Value)
	{
		return ((Value & (Value - 1)) == 0);
	}


	// Math Operations

	/** Returns highest of 3 values */
	template< class T >
	static FORCEINLINE T Max3(const T A, const T B, const T C)
	{
		return Max(Max(A, B), C);
	}

	/** Returns lowest of 3 values */
	template< class T >
	static FORCEINLINE T Min3(const T A, const T B, const T C)
	{
		return Min(Min(A, B), C);
	}

	/** Multiples value by itself */
	template< class T >
	static FORCEINLINE T Square(const T A)
	{
		return A*A;
	}

	/** Clamps X to be between Min and Max, inclusive */
	template< class T >
	static FORCEINLINE T Clamp(const T X, const T Min, const T Max)
	{
		return X<Min ? Min : X<Max ? X : Max;
	}

	/** Snaps a value to the nearest grid multiple */
	static FORCEINLINE float GridSnap(float Location, float Grid)
	{
		if (Grid == 0.f)	return Location;
		else
		{
			return FloorToFloat((Location + 0.5f*Grid) / Grid)*Grid;
		}
	}

	/** Snaps a value to the nearest grid multiple */
	static FORCEINLINE double GridSnap(double Location, double Grid)
	{
		if (Grid == 0.0)	return Location;
		else
		{
			return FloorToDouble((Location + 0.5*Grid) / Grid)*Grid;
		}
	}

	/** Divides two integers and rounds up */
	template <class T>
	static FORCEINLINE T DivideAndRoundUp(T Dividend, T Divisor)
	{
		return (Dividend + Divisor - 1) / Divisor;
	}

	template <class T>
	static FORCEINLINE T DivideAndRoundDown(T Dividend, T Divisor)
	{
		return Dividend / Divisor;
	}

	// Conversion Functions

	/**
	* Converts radians to degrees.
	* @param	RadVal			Value in radians.
	* @return					Value in degrees.
	*/
	template<class T>
	static FORCEINLINE float RadiansToDegrees(T const& RadVal)
	{
		return RadVal * (180.f / PI);
	}

	/** This overload allows us to maintain double precision */
	static FORCEINLINE double RadiansToDegrees(double RadVal)
	{
		return RadVal * (180.f / PI);
	}

	/**
	* Converts degrees to radians.
	* @param	DegVal			Value in degrees.
	* @return					Value in radians.
	*/
	template<class T>
	static FORCEINLINE float DegreesToRadians(T const& DegVal)
	{
		return DegVal * (PI / 180.f);
	}

	/** This overload allows us to maintain double precision */
	static FORCEINLINE double DegreesToRadians(double DegVal)
	{
		return DegVal * (PI / 180.f);
	}

	/**
	* Clamps an arbitrary angle to be between the given angles.  Will clamp to nearest boundary.
	*
	* @param MinAngleDegrees	"from" angle that defines the beginning of the range of valid angles (sweeping clockwise)
	* @param MaxAngleDegrees	"to" angle that defines the end of the range of valid angles
	* @return Returns clamped angle in the range -180..180.
	*/
	static float ClampAngle(float AngleDegrees, float MinAngleDegrees, float MaxAngleDegrees);

	/** Find the smallest angle between two headings (in radians) */
	static float FindDeltaAngle(float A1, float A2)
	{
		// Find the difference
		float Delta = A2 - A1;

		// If change is larger than PI
		if (Delta > PI)
		{
			// Flip to negative equivalent
			Delta = Delta - (PI * 2.0f);
		}
		else if (Delta < -PI)
		{
			// Otherwise, if change is smaller than -PI
			// Flip to positive equivalent
			Delta = Delta + (PI * 2.0f);
		}

		// Return delta in [-PI,PI] range
		return Delta;
	}

	/** Given a heading which may be outside the +/- PI range, 'unwind' it back into that range. */
	static float UnwindRadians(float A)
	{
		while (A > PI)
		{
			A -= ((float)PI * 2.0f);
		}

		while (A < -PI)
		{
			A += ((float)PI * 2.0f);
		}

		return A;
	}

	/** Utility to ensure angle is between +/- 180 degrees by unwinding. */
	static float UnwindDegrees(float A)
	{
		while (A > 180.f)
		{
			A -= 360.f;
		}

		while (A < -180.f)
		{
			A += 360.f;
		}

		return A;
	}

	/** Returns a new rotation component value
	*
	* @param InCurrent is the current rotation value
	* @param InDesired is the desired rotation value
	* @param InDeltaRate is the rotation amount to apply
	*
	* @return a new rotation component value
	*/
	static float FixedTurn(float InCurrent, float InDesired, float InDeltaRate);

	/** Converts given Cartesian coordinate pair to Polar coordinate system. */
	static FORCEINLINE void CartesianToPolar(float X, float Y, float& OutRad, float& OutAng)
	{
		OutRad = Sqrt(Square(X) + Square(Y));
		OutAng = Atan2(Y, X);
	}
	/** Converts given Polar coordinate pair to Cartesian coordinate system. */
	static FORCEINLINE void PolarToCartesian(float Rad, float Ang, float& OutX, float& OutY)
	{
		OutX = Rad * Cos(Ang);
		OutY = Rad * Sin(Ang);
	}

	/**
	* Calculates the dotted distance of vector 'Direction' to coordinate system O(AxisX,AxisY,AxisZ).
	*
	* Orientation: (consider 'O' the first person view of the player, and 'Direction' a vector pointing to an enemy)
	* - positive azimuth means enemy is on the right of crosshair. (negative means left).
	* - positive elevation means enemy is on top of crosshair, negative means below.
	*
	* @Note: 'Azimuth' (.X) sign is changed to represent left/right and not front/behind. front/behind is the funtion's return value.
	*
	* @param	OutDotDist	.X = 'Direction' dot AxisX relative to plane (AxisX,AxisZ). (== Cos(Azimuth))
	*						.Y = 'Direction' dot AxisX relative to plane (AxisX,AxisY). (== Sin(Elevation))
	* @param	Direction	direction of target.
	* @param	AxisX		X component of reference system.
	* @param	AxisY		Y component of reference system.
	* @param	AxisZ		Z component of reference system.
	*
	* @return	true if 'Direction' is facing AxisX (Direction dot AxisX >= 0.f)
	*/
	//static bool GetDotDistance(Vector2D &OutDotDist, const Vector &Direction, const Vector &AxisX, const Vector &AxisY, const Vector &AxisZ);

	/**
	* Returns Azimuth and Elevation of vector 'Direction' in coordinate system O(AxisX,AxisY,AxisZ).
	*
	* Orientation: (consider 'O' the first person view of the player, and 'Direction' a vector pointing to an enemy)
	* - positive azimuth means enemy is on the right of crosshair. (negative means left).
	* - positive elevation means enemy is on top of crosshair, negative means below.
	*
	* @param	Direction		Direction of target.
	* @param	AxisX			X component of reference system.
	* @param	AxisY			Y component of reference system.
	* @param	AxisZ			Z component of reference system.
	*
	* @return	Vector2D	X = Azimuth angle (in radians) (-PI, +PI)
	*						Y = Elevation angle (in radians) (-PI/2, +PI/2)
	*/
	//static Vector2D GetAzimuthAndElevation(const Vector &Direction, const Vector &AxisX, const Vector &AxisY, const Vector &AxisZ);

	// Interpolation Functions

	/** Calculates the percentage along a line from MinValue to MaxValue that Value is. */
	static FORCEINLINE float GetRangePct(float MinValue, float MaxValue, float Value)
	{
		return (Value - MinValue) / (MaxValue - MinValue);
	}

	/** Same as above, but taking a 2d vector as the range. */
	//static float GetRangePct(Vector2D const& Range, float Value);

	/** Basically a Vector2d version of Lerp. */
	//static float GetRangeValue(Vector2D const& Range, float Pct);

	/**
	* For the given value in the input range, returns the corresponding value in the output range.
	* Useful for mapping one value range to another value range.  Output is clamped to the OutputRange.
	* e.g. given that velocities [50..100] correspond to a sound volume of [0.2..1.4], this makes it easy to
	*      find the volume for a velocity of 77.
	*/
	//static FORCEINLINE float GetMappedRangeValue(Vector2D const& InputRange, Vector2D const& OutputRange, float Value)
	//{
	//	float const ClampedPct = Clamp<float>(GetRangePct(InputRange, Value), 0.f, 1.f);
	//	return GetRangeValue(OutputRange, ClampedPct);
	//}

	/** Performs a linear interpolation between two values, Alpha ranges from 0-1 */
	template< class T, class U >
	static FORCEINLINE T Lerp(const T& A, const T& B, const U& Alpha)
	{
		return (T)(A + Alpha * (B - A));
	}

	/** Performs a linear interpolation between two values, Alpha ranges from 0-1. Handles full numeric range of T */
	template< class T >
	static FORCEINLINE T LerpStable(const T& A, const T& B, double Alpha)
	{
		return (T)((A * (1.0 - Alpha)) + (B * Alpha));
	}

	/** Performs a linear interpolation between two values, Alpha ranges from 0-1. Handles full numeric range of T */
	template< class T >
	static FORCEINLINE T LerpStable(const T& A, const T& B, float Alpha)
	{
		return (T)((A * (1.0f - Alpha)) + (B * Alpha));
	}

	/** Performs a 2D linear interpolation between four values values, FracX, FracY ranges from 0-1 */
	template< class T, class U >
	static FORCEINLINE T BiLerp(const T& P00, const T& P10, const T& P01, const T& P11, const U& FracX, const U& FracY)
	{
		return Lerp(
			Lerp(P00, P10, FracX),
			Lerp(P01, P11, FracX),
			FracY
			);
	}

	/**
	* Performs a cubic interpolation
	*
	* @param  P - end points
	* @param  T - tangent directions at end points
	* @param  Alpha - distance along spline
	*
	* @return  Interpolated value
	*/
	template< class T, class U >
	static FORCEINLINE T CubicInterp(const T& P0, const T& T0, const T& P1, const T& T1, const U& A)
	{
		const float A2 = A  * A;
		const float A3 = A2 * A;

		return (T)(((2 * A3) - (3 * A2) + 1) * P0) + ((A3 - (2 * A2) + A) * T0) + ((A3 - A2) * T1) + (((-2 * A3) + (3 * A2)) * P1);
	}

	/**
	* Performs a first derivative cubic interpolation
	*
	* @param  P - end points
	* @param  T - tangent directions at end points
	* @param  Alpha - distance along spline
	*
	* @return  Interpolated value
	*/
	template< class T, class U >
	static FORCEINLINE T CubicInterpDerivative(const T& P0, const T& T0, const T& P1, const T& T1, const U& A)
	{
		T a = 6.f*P0 + 3.f*T0 + 3.f*T1 - 6.f*P1;
		T b = -6.f*P0 - 4.f*T0 - 2.f*T1 + 6.f*P1;
		T c = T0;

		const float A2 = A  * A;

		return (a * A2) + (b * A) + c;
	}

	/**
	* Performs a second derivative cubic interpolation
	*
	* @param  P - end points
	* @param  T - tangent directions at end points
	* @param  Alpha - distance along spline
	*
	* @return  Interpolated value
	*/
	template< class T, class U >
	static FORCEINLINE T CubicInterpSecondDerivative(const T& P0, const T& T0, const T& P1, const T& T1, const U& A)
	{
		T a = 12.f*P0 + 6.f*T0 + 6.f*T1 - 12.f*P1;
		T b = -6.f*P0 - 4.f*T0 - 2.f*T1 + 6.f*P1;

		return (a * A) + b;
	}

	/** Interpolate between A and B, applying an ease in function.  Exp controls the degree of the curve. */
	template< class T >
	static FORCEINLINE T InterpEaseIn(const T& A, const T& B, float Alpha, float Exp)
	{
		float const ModifiedAlpha = FMath::Pow(Alpha, Exp);
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolate between A and B, applying an ease out function.  Exp controls the degree of the curve. */
	template< class T >
	static FORCEINLINE T InterpEaseOut(const T& A, const T& B, float Alpha, float Exp)
	{
		float const ModifiedAlpha = 1.f - FMath::Pow(1.f - Alpha, Exp);
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolate between A and B, applying an ease in/out function.  Exp controls the degree of the curve. */
	template< class T >
	static FORCEINLINE T InterpEaseInOut(const T& A, const T& B, float Alpha, float Exp)
	{
		float const ModifiedAlpha = (Alpha < 0.5f) ?
			0.5f * Pow(2.f * Alpha, Exp) :
			1.f - 0.5f * Pow(2.f * (1.f - Alpha), Exp);

		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying a step function. */
	template< class T >
	static FORCEINLINE T InterpStep(const T& A, const T& B, float Alpha, int32 Steps)
	{
		if (Steps <= 1)
		{
			return A;
		}

		const float StepsAsFloat = static_cast<float>(Steps);
		const float NumIntervals = StepsAsFloat - 1.f;
		float const ModifiedAlpha = FloorToFloat(Alpha * StepsAsFloat) / NumIntervals;
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying a sinusoidal in function. */
	template< class T >
	static FORCEINLINE T InterpSinIn(const T& A, const T& B, float Alpha)
	{
		float const ModifiedAlpha = -1.f * cos(Alpha * HALF_PI) + 1.f;
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying a sinusoidal out function. */
	template< class T >
	static FORCEINLINE T InterpSinOut(const T& A, const T& B, float Alpha)
	{
		float const ModifiedAlpha = sin(Alpha * HALF_PI);
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying a sinusoidal in/out function. */
	template< class T >
	static FORCEINLINE T InterpSinInOut(const T& A, const T& B, float Alpha)
	{
		return (Alpha < 0.5f) ?
			InterpSinIn(A, B, Alpha * 2.f) * 0.5f :
			InterpSinOut(A, B, Alpha * 2.f - 1.f) * 0.5f + 0.5f;
	}

	/** Interpolation between A and B, applying an exponential in function. */
	template< class T >
	static FORCEINLINE T InterpExpoIn(const T& A, const T& B, float Alpha)
	{
		float const ModifiedAlpha = (Alpha == 0.f) ? 0.f : pow(2.f, 10.f * (Alpha - 1.f));
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying an exponential out function. */
	template< class T >
	static FORCEINLINE T InterpExpoOut(const T& A, const T& B, float Alpha)
	{
		float const ModifiedAlpha = (Alpha == 1.f) ? 1.f : -pow(2.f, -10.f * Alpha) + 1.f;
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying an exponential in/out function. */
	template< class T >
	static FORCEINLINE T InterpExpoInOut(const T& A, const T& B, float Alpha)
	{
		return (Alpha < 0.5f) ?
			InterpExpoIn(A, B, Alpha * 2.f) * 0.5f :
			InterpExpoOut(A, B, Alpha * 2.f - 1.f) * 0.5f + 0.5f;
	}

	/** Interpolation between A and B, applying a circular in function. */
	template< class T >
	static FORCEINLINE T InterpCircularIn(const T& A, const T& B, float Alpha)
	{
		float const ModifiedAlpha = -1.f * (Sqrt(1.f - Alpha * Alpha) - 1.f);
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying a circular out function. */
	template< class T >
	static FORCEINLINE T InterpCircularOut(const T& A, const T& B, float Alpha)
	{
		Alpha -= 1.f;
		float const ModifiedAlpha = Sqrt(1.f - Alpha  * Alpha);
		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/** Interpolation between A and B, applying a circular in/out function. */
	template< class T >
	static FORCEINLINE T InterpCircularInOut(const T& A, const T& B, float Alpha)
	{
		return (Alpha < 0.5f) ?
			InterpCircularIn(A, B, Alpha * 2.f) * 0.5f :
			InterpCircularOut(A, B, Alpha * 2.f - 1.f) * 0.5f + 0.5f;
	}

	// Rotator specific interpolation
	//template< class U > static FRotator Lerp(const FRotator& A, const FRotator& B, const U& Alpha);

	// Quat-specific interpolation

	//template< class U > static FQuat Lerp(const FQuat& A, const FQuat& B, const U& Alpha);
	//template< class U > static FQuat BiLerp(const FQuat& P00, const FQuat& P10, const FQuat& P01, const FQuat& P11, float FracX, float FracY);

	/**
	* In the case of quaternions, we use a bezier like approach.
	* T - Actual 'control' orientations.
	*/
	//template< class U > static FQuat CubicInterp(const FQuat& P0, const FQuat& T0, const FQuat& P1, const FQuat& T1, const U& A);

	/*
	*	Cubic Catmull-Rom Spline interpolation. Based on http://www.cemyuksel.com/research/catmullrom_param/catmullrom.pdf
	*	Curves are guaranteed to pass through the control points and are easily chained together.
	*	Equation supports abitrary parameterization. eg. Uniform=0,1,2,3 ; chordal= |Pn - Pn-1| ; centripetal = |Pn - Pn-1|^0.5
	*	P0 - The control point preceding the interpolation range.
	*	P1 - The control point starting the interpolation range.
	*	P2 - The control point ending the interpolation range.
	*	P3 - The control point following the interpolation range.
	*	T0-3 - The interpolation parameters for the corresponding control points.
	*	T - The interpolation factor in the range 0 to 1. 0 returns P1. 1 returns P2.
	*/
	template< class U > static U CubicCRSplineInterp(const U& P0, const U& P1, const U& P2, const U& P3, const float T0, const float T1, const float T2, const float T3, const float T);

	/* Same as CubicCRSplineInterp but with additional saftey checks. If the checks fail P1 is returned. **/
	template< class U > static U CubicCRSplineInterpSafe(const U& P0, const U& P1, const U& P2, const U& P3, const float T0, const float T1, const float T2, const float T3, const float T);

	// Special-case interpolation

	/** Interpolate a normal vector Current to Target, by interpolating the angle between those vectors with constant step. */
	static Vector VInterpNormalRotationTo(const Vector& Current, const Vector& Target, float DeltaTime, float RotationSpeedDegrees);

	/** Interpolate vector from Current to Target with constant step */
	static Vector VInterpConstantTo(const Vector Current, const Vector& Target, float DeltaTime, float InterpSpeed);

	/** Interpolate vector from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static Vector VInterpTo(const Vector& Current, const Vector& Target, float DeltaTime, float InterpSpeed);

	/** Interpolate vector2D from Current to Target with constant step */
	//static Vector2D Vector2DInterpConstantTo(const Vector2D& Current, const Vector2D& Target, float DeltaTime, float InterpSpeed);

	/** Interpolate vector2D from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	//static Vector2D Vector2DInterpTo(const Vector2D& Current, const Vector2D& Target, float DeltaTime, float InterpSpeed);

	/** Interpolate rotator from Current to Target with constant step */
	//static Rotator RInterpConstantTo(const FRotator& Current, const FRotator& Target, float DeltaTime, float InterpSpeed);

	/** Interpolate rotator from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	//static Rotator RInterpTo(const FRotator& Current, const FRotator& Target, float DeltaTime, float InterpSpeed);

	/** Interpolate float from Current to Target with constant step */
	static float FInterpConstantTo(float Current, float Target, float DeltaTime, float InterpSpeed);

	/** Interpolate float from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static float FInterpTo(float Current, float Target, float DeltaTime, float InterpSpeed);

	/** Interpolate Linear Color from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	//static LinearColor CInterpTo(const LinearColor& Current, const LinearColor& Target, float DeltaTime, float InterpSpeed);

	/**
	* Simple function to create a pulsating scalar value
	*
	* @param  InCurrentTime  Current absolute time
	* @param  InPulsesPerSecond  How many full pulses per second?
	* @param  InPhase  Optional phase amount, between 0.0 and 1.0 (to synchronize pulses)
	*
	* @return  Pulsating value (0.0-1.0)
	*/
	static float MakePulsatingValue(const double InCurrentTime, const float InPulsesPerSecond, const float InPhase = 0.0f)
	{
		return 0.5f + 0.5f * (float)sin(((0.25f + InPhase) * PI * 2.0) + (InCurrentTime * PI * 2.0) * InPulsesPerSecond);
	}

	// Geometry intersection 


	/**
	* Find the intersection of an infinite line (defined by two points) and
	* a plane.  Assumes that the line and plane do indeed intersect; you must
	* make sure they're not parallel before calling.
	*/
	static Vector LinePlaneIntersection(const Vector &Point1, const Vector &Point2, const Vector &PlaneOrigin, const Vector &PlaneNormal);
	//static Vector LinePlaneIntersection(const Vector &Point1, const Vector &Point2, const Plane  &Plane);

	/**
	* Determine if a plane and an AABB intersect
	* @param P - the plane to test
	* @param AABB - the axis aligned bounding box to test
	* @return if collision occurs
	*/
	//static bool PlaneAABBIntersection(const Plane& P, const Box& AABB);

	/**
	* Performs a sphere vs box intersection test using Arvo's algorithm:
	*
	*	for each i in (x, y, z)
	*		if (SphereCenter(i) < BoxMin(i)) d2 += (SphereCenter(i) - BoxMin(i)) ^ 2
	*		else if (SphereCenter(i) > BoxMax(i)) d2 += (SphereCenter(i) - BoxMax(i)) ^ 2
	*
	* @param Sphere the center of the sphere being tested against the AABB
	* @param RadiusSquared the size of the sphere being tested
	* @param AABB the box being tested against
	*
	* @return Whether the sphere/box intersect or not.
	*/
	//static bool SphereAABBIntersection(const Vector& SphereCenter, const float RadiusSquared, const Box& AABB);

	/**
	* Converts a sphere into a point plus radius squared for the test above
	*/
	//static bool SphereAABBIntersection(const Shpere& sphere, const Box& AABB);

	/** Determines whether a point is inside a box. */
	//static bool PointBoxIntersection(const Vector& Point, const Box& Box);

	/** Determines whether a line intersects a box. */
	//static bool LineBoxIntersection(const Box& Box, const Vector& Start, const Vector& End, const Vector& Direction);

	/** Determines whether a line intersects a box. This overload avoids the need to do the reciprocal every time. */
	//static bool LineBoxIntersection(const Box& Box, const Vector& Start, const Vector& End, const Vector& Direction, const Vector& OneOverDirection);

	/* Swept-Box vs Box test */
	//static bool LineExtentBoxIntersection(const Box& inBox, const Vector& Start, const Vector& End, const Vector& Extent, Vector& HitLocation, Vector& HitNormal, float& HitTime);

	/** Determines whether a line intersects a sphere. */
	static bool LineSphereIntersection(const Vector& Start, const Vector& Dir, float Length, const Vector& Origin, float Radius);

	/**
	* Assumes the cone tip is at 0,0,0 (means the SphereCenter is relative to the cone tip)
	* @return true: cone and sphere do intersect, false otherwise
	*/
	static bool SphereConeIntersection(const Vector& SphereCenter, float SphereRadius, const Vector& ConeAxis, float ConeAngleSin, float ConeAngleCos);

	/** Find the point on line segment from LineStart to LineEnd which is closest to Point */
	static Vector ClosestPointOnLine(const Vector& LineStart, const Vector& LineEnd, const Vector& Point);

	/** Compute intersection point of three planes. Return 1 if valid, 0 if infinite. */
	//static bool IntersectPlanes3(Vector& I, const Plane& P1, const Plane& P2, const Plane& P3);

	/**
	* Compute intersection point and direction of line joining two planes.
	* Return 1 if valid, 0 if infinite.
	*/
	//static bool IntersectPlanes2(Vector& I, Vector& D, const Plane& P1, const Plane& P2);

	/**
	* Calculates the distance of a given Point in world space to a given line,
	* defined by the vector couple (Origin, Direction).
	*
	* @param	Point				point to check distance to Axis
	* @param	Direction			unit vector indicating the direction to check against
	* @param	Origin				point of reference used to calculate distance
	* @param	OutClosestPoint	optional point that represents the closest point projected onto Axis
	*
	* @return	distance of Point from line defined by (Origin, Direction)
	*/
	static float PointDistToLine(const Vector &Point, const Vector &Line, const Vector &Origin, Vector &OutClosestPoint);
	static float PointDistToLine(const Vector &Point, const Vector &Line, const Vector &Origin);

	/**
	* Returns closest point on a segment to a given point.
	* The idea is to project point on line formed by segment.
	* Then we see if the closest point on the line is outside of segment or inside.
	*
	* @param	Point			point for which we find the closest point on the segment
	* @param	StartPoint		StartPoint of segment
	* @param	EndPoint		EndPoint of segment
	*
	* @return	point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
	*/
	static Vector ClosestPointOnSegment(const Vector &Point, const Vector &StartPoint, const Vector &EndPoint);

	/**
	* Vector2D version of ClosestPointOnSegment.
	* Returns closest point on a segment to a given 2D point.
	* The idea is to project point on line formed by segment.
	* Then we see if the closest point on the line is outside of segment or inside.
	*
	* @param	Point			point for which we find the closest point on the segment
	* @param	StartPoint		StartPoint of segment
	* @param	EndPoint		EndPoint of segment
	*
	* @return	point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
	*/
	//static Vector2D ClosestPointOnSegment2D(const Vector2D &Point, const Vector2D &StartPoint, const Vector2D &EndPoint);

	/**
	* Returns distance from a point to the closest point on a segment.
	*
	* @param	Point			point to check distance for
	* @param	StartPoint		StartPoint of segment
	* @param	EndPoint		EndPoint of segment
	*
	* @return	closest distance from Point to segment defined by (StartPoint, EndPoint).
	*/
	static float PointDistToSegment(const Vector &Point, const Vector &StartPoint, const Vector &EndPoint);

	/**
	* Returns square of the distance from a point to the closest point on a segment.
	*
	* @param	Point			point to check distance for
	* @param	StartPoint		StartPoint of segment
	* @param	EndPoint		EndPoint of segment
	*
	* @return	square of the closest distance from Point to segment defined by (StartPoint, EndPoint).
	*/
	static float PointDistToSegmentSquared(const Vector &Point, const Vector &StartPoint, const Vector &EndPoint);

	/**
	* Find closest points between 2 segments.
	* @param	(A1, B1)	defines the first segment.
	* @param	(A2, B2)	defines the second segment.
	* @param	OutP1		Closest point on segment 1 to segment 2.
	* @param	OutP2		Closest point on segment 2 to segment 1.
	*/
	static void SegmentDistToSegment(Vector A1, Vector B1, Vector A2, Vector B2, Vector& OutP1, Vector& OutP2);

	/**
	* Find closest points between 2 segments.
	* @param	(A1, B1)	defines the first segment.
	* @param	(A2, B2)	defines the second segment.
	* @param	OutP1		Closest point on segment 1 to segment 2.
	* @param	OutP2		Closest point on segment 2 to segment 1.
	*/
	static void SegmentDistToSegmentSafe(Vector A1, Vector B1, Vector A2, Vector B2, Vector& OutP1, Vector& OutP2);

	/**
	* returns the time (t) of the intersection of the passed segment and a plane (could be <0 or >1)
	* @param StartPoint - start point of segment
	* @param EndPoint   - end point of segment
	* @param Plane		- plane to intersect with
	* @return time(T) of intersection
	*/
	//static float GetTForSegmentPlaneIntersect(const Vector& StartPoint, const Vector& EndPoint, const Plane& Plane);

	/**
	* Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
	* the plane on which polygon Plane lies. If there is an intersection, the point is placed in IntersectionPoint
	* @param StartPoint - start point of segment
	* @param EndPoint   - end point of segment
	* @param Plane		- plane to intersect with
	* @param out_InterSectPoint - out var for the point on the segment that intersects the mesh (if any)
	* @return true if intersection occured
	*/
	//static bool SegmentPlaneIntersection(const Vector& StartPoint, const Vector& EndPoint, const Plane& Plane, Vector& out_IntersectPoint);

	/**
	* Returns closest point on a triangle to a point.
	* The idea is to identify the halPlanes that the point is
	* in relative to each triangle segment "plane"
	*
	* @param	Point			point to check distance for
	* @param	A,B,C			counter clockwise ordering of points defining a triangle
	*
	* @return	Point on triangle ABC closest to given point
	*/
	static Vector ClosestPointOnTriangleToPoint(const Vector& Point, const Vector& A, const Vector& B, const Vector& C);

	/**
	* Returns closest point on a tetrahedron to a point.
	* The idea is to identify the halPlanes that the point is
	* in relative to each face of the tetrahedron
	*
	* @param	Point			point to check distance for
	* @param	A,B,C,D			four points defining a tetrahedron
	*
	* @return	Point on tetrahedron ABCD closest to given point
	*/
	static Vector ClosestPointOnTetrahedronToPoint(const Vector& Point, const Vector& A, const Vector& B, const Vector& C, const Vector& D);

	/**
	* Find closest point on a Sphere to a Line.
	* When line intersects		Sphere, then closest point to LineOrigin is returned.
	* @param SphereOrigin		Origin of Sphere
	* @param SphereRadius		Radius of Sphere
	* @param LineOrigin		Origin of line
	* @param LineDir			Direction of line. Needs to be normalized!!
	* @param OutClosestPoint	Closest point on sphere to given line.
	*/
	static void SphereDistToLine(Vector SphereOrigin, float SphereRadius, Vector LineOrigin, Vector LineDir, Vector& OutClosestPoint);

	/**
	* Calculates whether a Point is within a cone segment, and also what percentage within the cone (100% is along the center line, whereas 0% is along the edge)
	*
	* @param Point - The Point in question
	* @param ConeStartPoint - the beginning of the cone (with the smallest radius)
	* @param ConeLine - the line out from the start point that ends at the largest radius point of the cone
	* @param radiusAtStart - the radius at the ConeStartPoint (0 for a 'proper' cone)
	* @param radiusAtEnd - the largest radius of the cone
	* @param percentageOut - output variable the holds how much within the cone the point is (1 = on center line, 0 = on exact edge or outside cone).
	*
	* @return true if the point is within the cone, false otherwise.
	*/
	static bool GetDistanceWithinConeSegment(Vector Point, Vector ConeStartPoint, Vector ConeLine, float RadiusAtStart, float RadiusAtEnd, float &PercentageOut);

	/**
	* Determines whether a given set of points are coplanar, with a tolerance. Any three points or less are always coplanar.
	*
	* @param Points - The set of points to determine coplanarity for.
	* @param Tolerance - Larger numbers means more variance is allowed.
	*
	* @return Whether the points are relatively coplanar, based on the tolerance
	*/
	//static bool PointsAreCoplanar(const TArray<Vector>& Points, const float Tolerance = 0.1f);


	// Utilities

	/**
	* Tests a memory region to see that it's working properly.
	*
	* @param BaseAddress	Starting address
	* @param NumBytes		Number of bytes to test (will be rounded down to a multiple of 4)
	* @return				true if the memory region passed the test
	*/
	static bool MemoryTest(void* BaseAddress, uint32 NumBytes);

	/**
	* Computes the barycentric coordinates for a given point in a triangle - simpler version
	*
	* @param	Point			point to convert to barycentric coordinates (in plane of ABC)
	* @param	A,B,C			three non-colinear points defining a triangle in CCW
	*
	* @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
	*							                                or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
	*/
	static Vector GetBaryCentric2D(const Vector& Point, const Vector& A, const Vector& B, const Vector& C);

	/**
	* Computes the barycentric coordinates for a given point in a triangle
	*
	* @param	Point			point to convert to barycentric coordinates (in plane of ABC)
	* @param	A,B,C			three non-collinear points defining a triangle in CCW
	*
	* @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
	*							                               or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
	*/
	static Vector ComputeBaryCentric2D(const Vector& Point, const Vector& A, const Vector& B, const Vector& C);

	/**
	* Computes the barycentric coordinates for a given point on a tetrahedron (3D)
	*
	* @param	Point			point to convert to barycentric coordinates
	* @param	A,B,C,D			four points defining a tetrahedron
	*
	* @return Vector containing the four weights a,b,c,d such that Point = a*A + b*B + c*C + d*D
	*/
	static Vector4 ComputeBaryCentric3D(const Vector& Point, const Vector& A, const Vector& B, const Vector& C, const Vector& D);

	/** 32 bit values where BitFlag[x] == (1<<x) */
	static const uint32 BitFlag[32];

	/**
	* Returns a smooth Hermite interpolation between 0 and 1 for the value X (where X ranges between A and B)
	* Clamped to 0 for X <= A and 1 for X >= B.
	*
	* @param A Minimum value of X
	* @param B Maximum value of X
	* @param X Parameter
	*
	* @return Smoothed value between 0 and 1
	*/
	static float SmoothStep(float A, float B, float X)
	{
		if (X < A)
		{
			return 0.0f;
		}
		else if (X >= B)
		{
			return 1.0f;
		}
		const float InterpFraction = (X - A) / (B - A);
		return InterpFraction * InterpFraction * (3.0f - 2.0f * InterpFraction);
	}

	/**
	* Get a bit in memory created from bitflags (uint32 Value:1), used for EngineShowFlags,
	* TestBitFieldFunctions() tests the implementation
	*/
	static inline bool ExtractBoolFromBitfield(uint8* Ptr, uint32 Index)
	{
		uint8* BytePtr = Ptr + Index / 8;
		uint8 Mask = 1 << (Index & 0x7);

		return (*BytePtr & Mask) != 0;
	}

	/**
	* Set a bit in memory created from bitflags (uint32 Value:1), used for EngineShowFlags,
	* TestBitFieldFunctions() tests the implementation
	*/
	static inline void SetBoolInBitField(uint8* Ptr, uint32 Index, bool bSet)
	{
		uint8* BytePtr = Ptr + Index / 8;
		uint8 Mask = 1 << (Index & 0x7);

		if (bSet)
		{
			*BytePtr |= Mask;
		}
		else
		{
			*BytePtr &= ~Mask;
		}
	}
};

///** Float specialization */
//template<>
//FORCEINLINE float Math::Abs(const float A)
//{
//	return fabsf(A);
//}