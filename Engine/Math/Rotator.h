//===========================================================================
// Rotator:
//===========================================================================
// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "MathUtility.h"
#include "Vector.h"
#include "Quaternion.h"

/**
* Implements a container for rotation information.
*
* All rotation values are stored in degrees.
*/
struct Rotator
{
public:

	/** Looking up and down (0=Straight Ahead, +Up, -Down). */
	float Pitch;

	/** Rotating around (running in circles), 0=East, +North, -South. */
	float Yaw;

	/** Rotation about axis of screen, 0=Straight, +Clockwise, -CCW. */
	float Roll;

public:

	/** A rotator of zero degrees on each axis. */
	static const Rotator ZeroRotator;

public:

	/**
	* Default constructor (no initialization).
	*/
	FORCEINLINE Rotator() { };

	/**
	* Constructor
	*
	* @param InF Value to set all components to.
	*/
	explicit FORCEINLINE Rotator(float InF);

	/**
	* Constructor.
	*
	* @param InPitch Pitch in degrees.
	* @param InYaw Yaw in degrees.
	* @param InRoll Roll in degrees.
	*/
	FORCEINLINE Rotator(float InPitch, float InYaw, float InRoll);

	/**
	* Constructor.
	*
	* @param Quat Quaternion used to specify rotation.
	*/
	explicit Rotator(const Quaternion& Quat);

public:

	// Binary arithmetic operators.

	/**
	* Get the result of adding a rotator to this.
	*
	* @param R The other rotator.
	* @return The result of adding a rotator to this.
	*/
	Rotator operator+(const Rotator &R) const;

	/**
	* Get the result of subtracting a rotator from this.
	*
	* @param R The other rotator.
	* @return The result of subtracting a rotator from this.
	*/
	Rotator operator-(const Rotator &R) const;

	/**
	* Get the result of scaling this rotator.
	*
	* @param Scale The scaling factor.
	* @return The result of scaling.
	*/
	Rotator operator*(float Scale) const;

	/**
	* Multiply this rotator by a scaling factor.
	*
	* @param Scale The scaling factor.
	* @return Copy of the rotator after scaling.
	*/
	Rotator operator*=(float Scale);

	// Unary operators.

	/**
	* Get a negated copy of the rotator.
	*
	* @return A negated copy of the rotator.
	*/
	FORCEINLINE Rotator operator-() const;

	// Binary comparison operators.

	/**
	* Checks whether two rotators are identical.
	*
	* @param R The other rotator.
	* @return true if two rotators are identical, otherwise false.
	*/
	bool operator==(const Rotator &R) const;

	/**
	* Checks whether two rotators are different.
	*
	* @param V The other rotator.
	* @return true if two rotators are different, otherwise false.
	*/
	bool operator!=(const Rotator &V) const;

	// Assignment operators.

	/**
	* Adds another rotator to this.
	*
	* @param R The other rotator.
	* @return Copy of rotator after addition.
	*/
	Rotator operator+=(const Rotator &R);

	/**
	* Subtracts another rotator from this.
	*
	* @param R The other rotator.
	* @return Copy of rotator after subtraction.
	*/
	Rotator operator-=(const Rotator &R);

public:

	// Functions.

	/**
	* Checks whether rotator is nearly zero, within specified tolerance.
	*
	* @param Tolerance Error Tolerance.
	* @return true if rotator is nearly zero, within specified tolerance, otherwise false.
	*/
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Checks whether this has exactly zero rotation.
	*
	* @return true if this has exactly zero rotation, otherwise false.
	*/
	bool IsZero() const;

	/**
	* Checks whether two rotators are equal, within specified tolerance.
	*
	* @param R The other rotator.
	* @param Tolerance Error Tolerance.
	* @return true if two rotators are equal, within specified tolerance, otherwise false.
	*/
	bool Equals(const Rotator &R, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Adds to each component of the rotator.
	*
	* @param DeltaPitch Change in pitch. (+/-)
	* @param DeltaYaw Change in yaw. (+/-)
	* @param DeltaRoll Change in roll. (+/-)
	* @return Copy of rotator after addition.
	*/
	Rotator Add(float DeltaPitch, float DeltaYaw, float DeltaRoll);

	/**
	* Get the rotation, snapped to specified degree segments.
	*
	* @param RotGrid A Rotator specifying how to snap each component.
	* @return Snapped version of rotation.
	*/
	Rotator GridSnap(const Rotator &RotGrid) const;

	/**
	* Convert a rotation into a vector facing in its direction.
	*
	* @return Rotation as a direction vector.
	*/
	Vector toVector() const;

	/**
	* Get Rotation as a quaternion.
	*
	* @return Rotation as a quaternion.
	*/
	Quaternion Quaternion() const;

	/**
	* Convert a Rotator into floating-point Euler angles (in degrees). Rotator now stored in degrees.
	*
	* @return Rotation as a Euler angle vector.
	*/
	Vector Euler() const;

	/**
	* Rotate a vector rotated by this rotator.
	*
	* @param V The vector to rotate.
	* @return The rotated vector.
	*/
	Vector RotateVector(const Vector& V) const;

	/**
	* Returns the vector rotated by the inverse of this rotator.
	*
	* @param V The vector to rotate.
	* @return The rotated vector.
	*/
	Vector UnrotateVector(const Vector& V) const;

	/**
	* Gets the rotation values so they fall within the range [0,360]
	*
	* @return Clamped version of rotator.
	*/
	Rotator Clamp() const;

	/**
	* Create a copy of this rotator and normalize, removes all winding and creates the "shortest route" rotation.
	*
	* @return Normalized copy of this rotator
	*/
	Rotator GetNormalized() const;

	/**
	* Create a copy of this rotator and denormalize, clamping each axis to 0 - 360.
	*
	* @return Denormalized copy of this rotator
	*/
	Rotator GetDenormalized() const;

	/**
	* In-place normalize, removes all winding and creates the "shortest route" rotation.
	*/
	void Normalize();

	/**
	* Decompose this Rotator into a Winding part (multiples of 360) and a Remainder part.
	* Remainder will always be in [-180, 180] range.
	*
	* @param Winding[Out] the Winding part of this Rotator
	* @param Remainder[Out] the Remainder
	*/
	void GetWindingAndRemainder(Rotator& Winding, Rotator& Remainder) const;

	/**
	* Utility to check if there are any NaNs in this Rotator.
	*
	* @return true if there are any NaNs in this Rotator, otherwise false.
	*/
	bool ContainsNaN() const;

public:

	/**
	* Clamps an angle to the range of [0, 360].
	*
	* @param Angle The angle to clamp.
	* @return The clamped angle.
	*/
	static float ClampAxis(float Angle);

	/**
	* Clamps an angle to the range of [-180, 180].
	*
	* @param Angle The Angle to clamp.
	* @return The clamped angle.
	*/
	static float NormalizeAxis(float Angle);

	/**
	* Compresses a floating point angle into a byte.
	*
	* @param Angle The angle to compress.
	* @return The angle as a byte.
	*/
	static uint8 CompressAxisToByte(float Angle);

	/**
	* Decompress a word into a floating point angle.
	*
	* @param Angle The word angle.
	* @return The decompressed angle.
	*/
	static float DecompressAxisFromByte(uint16 Angle);

	/**
	* Compress a floating point angle into a word.
	*
	* @param Angle The angle to compress.
	* @return The decompressed angle.
	*/
	static uint16 CompressAxisToShort(float Angle);

	/**
	* Decompress a short into a floating point angle.
	*
	* @param Angle The word angle.
	* @return The decompressed angle.
	*/
	static float DecompressAxisFromShort(uint16 Angle);

	/**
	* Convert a vector of floating-point Euler angles (in degrees) into a Rotator. Rotator now stored in degrees
	*
	* @param Euler Euler angle vector.
	* @return A rotator from a Euler angle.
	*/
	static Rotator MakeFromEuler(const Vector& Euler);

};


/* Rotator inline functions
*****************************************************************************/

/**
* Scale a rotator and return.
*
* @param Scale scale to apply to R.
* @param R rotator to be scaled.
* @return Scaled rotator.
*/
FORCEINLINE Rotator operator*(float Scale, const Rotator &R)
{
	return R.operator*(Scale);
}


FORCEINLINE Rotator::Rotator(float InF)
	: Pitch(InF), Yaw(InF), Roll(InF)
{}


FORCEINLINE Rotator::Rotator(float InPitch, float InYaw, float InRoll)
	: Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
{}


FORCEINLINE Rotator Rotator::operator+(const Rotator &R) const
{
	return Rotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll);
}


FORCEINLINE Rotator Rotator::operator-(const Rotator &R) const
{
	return Rotator(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll);
}


FORCEINLINE Rotator Rotator::operator*(float Scale) const
{
	return Rotator(Pitch*Scale, Yaw*Scale, Roll*Scale);
}


FORCEINLINE Rotator Rotator::operator*= (float Scale)
{
	Pitch = Pitch*Scale; Yaw = Yaw*Scale; Roll = Roll*Scale;
	return *this;
}


FORCEINLINE Rotator Rotator::operator-() const
{
	return Rotator(-Pitch, -Yaw, -Roll);
}


FORCEINLINE bool Rotator::operator==(const Rotator &R) const
{
	return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
}


FORCEINLINE bool Rotator::operator!=(const Rotator &V) const
{
	return Pitch != V.Pitch || Yaw != V.Yaw || Roll != V.Roll;
}


FORCEINLINE Rotator Rotator::operator+=(const Rotator &R)
{
	Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
	return *this;
}


FORCEINLINE Rotator Rotator::operator-=(const Rotator &R)
{
	Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll;
	return *this;
}


FORCEINLINE bool Rotator::IsNearlyZero(float Tolerance) const
{
	return
		Math::Abs(NormalizeAxis(Pitch))<Tolerance
		&&	Math::Abs(NormalizeAxis(Yaw))<Tolerance
		&&	Math::Abs(NormalizeAxis(Roll))<Tolerance;
}


FORCEINLINE bool Rotator::IsZero() const
{
	return (ClampAxis(Pitch) == 0.f) && (ClampAxis(Yaw) == 0.f) && (ClampAxis(Roll) == 0.f);
}


FORCEINLINE bool Rotator::Equals(const Rotator &R, float Tolerance) const
{
	return (Math::Abs(NormalizeAxis(Pitch - R.Pitch)) < Tolerance)
		&& (Math::Abs(NormalizeAxis(Yaw - R.Yaw)) < Tolerance)
		&& (Math::Abs(NormalizeAxis(Roll - R.Roll)) < Tolerance);
}


FORCEINLINE Rotator Rotator::Add(float DeltaPitch, float DeltaYaw, float DeltaRoll)
{
	Yaw += DeltaYaw;
	Pitch += DeltaPitch;
	Roll += DeltaRoll;
	return *this;
}


FORCEINLINE Rotator Rotator::GridSnap(const Rotator &RotGrid) const
{
	return Rotator
		(
		Math::GridSnap(Pitch, RotGrid.Pitch),
		Math::GridSnap(Yaw, RotGrid.Yaw),
		Math::GridSnap(Roll, RotGrid.Roll)
		);
}


FORCEINLINE Rotator Rotator::Clamp() const
{
	return Rotator(ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll));
}


FORCEINLINE float Rotator::ClampAxis(float Angle)
{
	// returns Angle in the range (-360,360)
	Angle = Math::Fmod(Angle, 360.f);

	if (Angle < 0.f)
	{
		// shift to [0,360) range
		Angle += 360.f;
	}

	return Angle;
}


FORCEINLINE float Rotator::NormalizeAxis(float Angle)
{
	// returns Angle in the range [0,360)
	Angle = ClampAxis(Angle);

	if (Angle > 180.f)
	{
		// shift to (-180,180]
		Angle -= 360.f;
	}

	return Angle;
}


FORCEINLINE uint8 Rotator::CompressAxisToByte(float Angle)
{
	// map [0->360) to [0->256) and mask off any winding
	return Math::RoundToInt(Angle * 256.f / 360.f) & 0xFF;
}


FORCEINLINE float Rotator::DecompressAxisFromByte(uint16 Angle)
{
	// map [0->256) to [0->360)
	return (Angle * 360.f / 256.f);
}


FORCEINLINE uint16 Rotator::CompressAxisToShort(float Angle)
{
	// map [0->360) to [0->65536) and mask off any winding
	return Math::RoundToInt(Angle * 65536.f / 360.f) & 0xFFFF;
}


FORCEINLINE float Rotator::DecompressAxisFromShort(uint16 Angle)
{
	// map [0->65536) to [0->360)
	return (Angle * 360.f / 65536.f);
}


FORCEINLINE Rotator Rotator::GetNormalized() const
{
	Rotator Rot = *this;
	Rot.Normalize();
	return Rot;
}


FORCEINLINE Rotator Rotator::GetDenormalized() const
{
	Rotator Rot = *this;
	Rot.Pitch = ClampAxis(Rot.Pitch);
	Rot.Yaw = ClampAxis(Rot.Yaw);
	Rot.Roll = ClampAxis(Rot.Roll);
	return Rot;
}


FORCEINLINE void Rotator::Normalize()
{
	Yaw = NormalizeAxis(Yaw);
	Pitch = NormalizeAxis(Pitch);
	Roll = NormalizeAxis(Roll);
}


FORCEINLINE bool Rotator::ContainsNaN() const
{
	return (Math::IsNaN(Pitch) || !Math::IsFinite(Pitch)
		|| Math::IsNaN(Yaw) || !Math::IsFinite(Yaw)
		|| Math::IsNaN(Roll) || !Math::IsFinite(Roll));
}

FORCEINLINE Vector Rotator::Euler() const
{
	return Vector(Roll, Pitch, Yaw);
}