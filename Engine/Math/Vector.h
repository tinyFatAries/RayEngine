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

	/* World up vector (0,1,0) */
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
	FORCEINLINE bool operator==(const Vector& V) const;

	/**
	* Check against another vector for inequality.
	*
	* @param V The vector to check against.
	* @return true if the vectors are not equal, false otherwise.
	*/
	FORCEINLINE bool operator!=(const Vector& V) const;

	/**
	* Check against another vector for equality, within specified error limits.
	*
	* @param V The vector to check against.
	* @param Tolerance Error tolerance.
	* @return true if the vectors are equal within tolerance limits, false otherwise.
	*/
	FORCEINLINE bool Equals(const Vector& V, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Checks whether all components of this vector are the same, within a tolerance.
	*
	* @param Tolerance Error tolerance.
	* @return true if the vectors are equal within tolerance limits, false otherwise.
	*/
	FORCEINLINE bool AllComponentsEqual(float Tolerance = KINDA_SMALL_NUMBER) const;

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
	FORCEINLINE Vector operator/=(float V);

	/**
	* Multiplies the vector with another vector, using component-wise multiplication.
	*
	* @param V What to multiply this vector with.
	* @return Copy of the vector after multiplication.
	*/
	FORCEINLINE Vector operator*=(const Vector& V);

	/**
	* Divides the vector by another vector, using component-wise division.
	*
	* @param V What to divide vector by.
	* @return Copy of the vector after division.
	*/
	FORCEINLINE Vector operator/=(const Vector& V);

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
	FORCEINLINE void Set(float InX, float InY, float InZ);

	/**
	* Get the maximum value of the vector's components.
	*
	* @return The maximum value of the vector's components.
	*/
	FORCEINLINE float GetMax() const;

	/**
	* Get the maximum absolute value of the vector's components.
	*
	* @return The maximum absolute value of the vector's components.
	*/
	FORCEINLINE float GetAbsMax() const;

	/**
	* Get the minimum value of the vector's components.
	*
	* @return The minimum value of the vector's components.
	*/
	FORCEINLINE float GetMin() const;

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