#include <iostream>
#include <math.h>

#include "RMath.h"

using namespace REng;
using namespace REng::Math;

//====================================================================================================
// Constants
//====================================================================================================

const float Math::kPi = 3.14159265358979f;
const float Math::kTwoPi = 6.28318530717958f;
const float Math::kPiByTwo = 1.57079632679489f;
const float Math::kRootTwo = 1.41421356237309f;
const float Math::kRootThree = 1.73205080756887f;
const float Math::kDegToRad = kPi / 180.0f;
const float Math::kRadToDeg = 180.0f / kPi;

//====================================================================================================
// Function Definitions
//====================================================================================================


Matrix4 Math::MatrixRotationAxis(const Vector3& axis, float rad)
{
	const Vector3 u = Normalize(axis);
	const float x = u.x;
	const float y = u.y;
	const float z = u.z;
	const float s = sin(rad);
	const float c = cos(rad);

	return Matrix4
	(
		c + (x * x * (1.0f - c)),
		x * y * (1.0f - c) + z * s,
		x * z * (1.0f - c) - y * s,
		0.0f,

		x * y * (1.0f - c) - z * s,
		c + (y * y * (1.0f - c)),
		y * z * (1.0f - c) + x * s,
		0.0f,

		x * z * (1.0f - c) + y * s,
		y * z * (1.0f - c) - x * s,
		c + (z * z * (1.0f - c)),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	);
}

//----------------------------------------------------------------------------------------------------

Matrix4 Math::QuaternionToMatrix(const Quaternion& q)
{
	return Matrix4
	(
		1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
		(2.0f * q.x * q.y) + (2.0f * q.z * q.w),
		(2.0f * q.x * q.z) - (2.0f * q.y * q.w),
		0.0f,

		(2.0f * q.x * q.y) - (2.0f * q.z * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
		(2.0f * q.y * q.z) + (2.0f * q.x * q.w),
		0.0f,

		(2.0f * q.x * q.z) + (2.0f * q.y * q.w),
		(2.0f * q.y * q.z) - (2.0f * q.x * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	);
}

//----------------------------------------------------------------------------------------------------

Math::Quaternion Math::Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	Quaternion q_0{ Math::Normalize(q0) };
	Quaternion q_1{ Math::Normalize(q1) };
	//Find the dot product 
	float dot = (q_0.x * q_1.x) + (q_0.y * q_1.y) + (q_0.z * q_1.z) + (q_0.w * q_1.w);

	//Determine the direction of the rotation 
	if (dot < 0.0f)
	{
		dot = -dot;
		q_1.x = -q_1.x;
		q_1.y = -q_1.y;
		q_1.z = -q_1.z;
		q_1.w = -q_1.w;
	}
	else if (dot > 0.9995f)
	{
		return (Lerp(q_0, q_1, t));
	}

	float theta_0 = acos(dot);
	float theta = theta_0 * t;
	float sinTheta = sin(theta);
	float sinTheta_0 = sin(theta_0);

	float s0 = cos(theta) - dot * sinTheta / sinTheta_0;
	float s1 = sinTheta / sinTheta_0;

	return (q_0 * s0) + (q_1 * s1);
}
//----------------------------------------------------------------------------------------------------
Math::Quaternion Math::EulerToQuaternion(float x, float y, float z)
{
	Quaternion q;
	float sx, sy, sz;
	float cx, cy, cz;
	sx = sinf(x * kDegToRad * 0.5f); sy = sinf(y * kDegToRad * 0.5f); sz = sinf(z * kDegToRad * 0.5f);
	cx = cosf(x * kDegToRad * 0.5f); cy = cosf(y * kDegToRad * 0.5f); cz = cosf(z * kDegToRad * 0.5f);

	q.w = (cx * cy * cz) + (sx * sy * sz);
	q.x = (sx * cy * cz) + (cx * sy * sz);
	q.y = (cx * sy * cz) - (sx * cy * sz);
	q.z = (cx * cy * sz) - (sx * sy * cz);


	q = Normalize(q);
	return q;
}

//----------------------------------------------------------------------------------------------------

Math::Vector3 Math::QuaternionToEuler(const Quaternion& q1)
{
	Vector3 eulerAngles;

	Quaternion q = Normalize(q1);

	// roll (z-axis rotation)
	float sinr = +2.0f * (q.w * q.x + q.y * q.z);
	float cosr = +1.0f - 2.0f * (q.x * q.x + q.y * q.y);
	eulerAngles.z = atan2(sinr, cosr) * kRadToDeg;

	// pitch (x-axis rotation)
	double sinp = +2.0 * (q.w * q.y - q.z * q.x);
	if (fabs(sinp) >= 1)
	{
		eulerAngles.x = static_cast<float>(copysign(kPi * 0.5f, sinp)) * kRadToDeg; // use 90 degrees if out of range
	}
	else
	{
		eulerAngles.x = static_cast<float>(asin(sinp)) * kRadToDeg;
	}

	// yaw (y-axis rotation)
	float siny = +2.0f * (q.w * q.z + q.x * q.y);
	float cosy = +1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	eulerAngles.y = atan2(siny, cosy) * kRadToDeg;


	return eulerAngles;
}
//----------------------------------------------------------------------------------------------------

Math::Quaternion Math::Conjugate(Quaternion q0)
{
	Quaternion q1;
	q1.w = q0.w;
	q1.x = -q0.x;
	q1.y = -q0.y;
	q1.z = -q0.z;

	return q1;
}

//----------------------------------------------------------------------------------------------------
Math::Quaternion Math::Inverse(Quaternion q0)
{
	Quaternion qInverse = Conjugate(q0) / MagnitudeSqr(q0);

	return qInverse;
}

//----------------------------------------------------------------------------------------------------
Math::Quaternion Math::LookRotation(const Vector3& look, const Vector3& up)
{
	Vector3 forward = Math::Normalize(look);
	Vector3 vector2 = Math::Normalize(Math::Cross(up, forward));
	Vector3 vector3 = Math::Cross(forward, vector2);

	float m00 = vector2.x;
	float m01 = vector2.y;
	float m02 = vector2.z;
	float m10 = vector3.x;
	float m11 = vector3.y;
	float m12 = vector3.z;
	float m20 = forward.x;
	float m21 = forward.y;
	float m22 = forward.z;

	float num8 = (m00 + m11) + m22;

	Quaternion quaternion;

	if (num8 > 0.0f)
	{
		float num = Sqrt(num8 + 1.0f);
		quaternion.w = num * 0.5f;
		num = 0.5f / num;
		quaternion.x = (m12 - m21) * num;
		quaternion.y = (m20 - m02) * num;
		quaternion.z = (m01 - m10) * num;

		return quaternion;
	}

	if ((m00 >= m11) && (m00 >= m22))
	{
		float num7 = Sqrt(((1.0f + m00) - m11) - m22);
		float num4 = 0.5f / num7;
		quaternion.x = 0.5f * num7;
		quaternion.y = (m01 + m10) * num4;
		quaternion.z = (m02 + m20) * num4;
		quaternion.w = (m12 - m21) * num4;
		return quaternion;
	}

	if (m11 > m22)
	{
		float num6 = Sqrt(((1.0f + m11) - m00) - m22);
		float num3 = 0.5f / num6;
		quaternion.x = (m10 + m01) * num3;
		quaternion.y = 0.5f * num6;
		quaternion.z = (m21 + m12) * num3;
		quaternion.w = (m20 - m02) * num3;
		return quaternion;
	}

	float num5 = Sqrt(((1.0f + m22) - m00) - m11);
	float num2 = 0.5f / num5;

	quaternion.x = (m20 + m02) * num2;
	quaternion.y = (m21 + m12) * num2;
	quaternion.z = 0.5f * num5;
	quaternion.w = (m01 - m10) * num2;
	return quaternion;

}

//----------------------------------------------------------------------------------------------------

Math::Quaternion Math::FromToQuaternion(const Vector3& from, const Vector3& to)
{
	Vector3 normalizedFrom = Normalize(from);
	Vector3 normalizedTo = Normalize(to);

	float c = Dot(normalizedFrom, normalizedTo);
	float angle = acos(c);
	Vector3 w = Normalize(Cross(from, to));
	return QuaternionFromAxisAngle(w, angle);
}

//----------------------------------------------------------------------------------------------------
Math::Quaternion Math::QuaternionFromAxisAngle(const Vector3& axis, float angleDegrees)
{
	Quaternion q;
	float angleRadians = angleDegrees * kDegToRad;
	float s = sin(angleRadians * 0.5f);

	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	q.w = cos(angleRadians * 0.5f);

	return q;
}

//----------------------------------------------------------------------------------------------------
Math::Quaternion Math::QuaternionFromMatrix(const Matrix4& mat)
{
	Matrix4 rotationMatrix = Transpose(mat);
	Quaternion q;

	float trace{ rotationMatrix._11 + rotationMatrix._22 + rotationMatrix._33 };

	if (trace > 0.0f)
	{
		float s = 0.5f / sqrt(trace + 1.0f);

		q.w = 0.25f / s;
		q.x = (rotationMatrix._32 - rotationMatrix._23) * s;
		q.y = (rotationMatrix._13 - rotationMatrix._31) * s;
		q.z = (rotationMatrix._21 - rotationMatrix._12) * s;
	}
	else
	{
		if (rotationMatrix._11 > rotationMatrix._22 && rotationMatrix._11 > rotationMatrix._33)
		{
			float s = 2.0f * sqrt(1.0f + rotationMatrix._11 - rotationMatrix._22 - rotationMatrix._33);
			q.x = 0.25f * s;
			q.y = (rotationMatrix._12 + rotationMatrix._21) / s;
			q.z = (rotationMatrix._13 + rotationMatrix._31) / s;
			q.w = (rotationMatrix._32 - rotationMatrix._23) / s;
		}
		else if (rotationMatrix._22 > rotationMatrix._33)
		{
			float s = 2.0f * sqrt(1.0f + rotationMatrix._22 - rotationMatrix._11 - rotationMatrix._33);
			q.x = (rotationMatrix._12 + rotationMatrix._21) / s;
			q.y = 0.25f * s;
			q.z = (rotationMatrix._23 + rotationMatrix._32) / s;
			q.w = (rotationMatrix._13 - rotationMatrix._31) / s;
		}
		else
		{
			float s = 2.0f * sqrt(1.0f + rotationMatrix._33 - rotationMatrix._11 - rotationMatrix._22);

			q.x = (rotationMatrix._13 + rotationMatrix._31) / s;
			q.y = (rotationMatrix._23 + rotationMatrix._32) / s;
			q.z = 0.25f * s;
			q.w = (rotationMatrix._21 - rotationMatrix._12) / s;
		}
	}

	return Normalize(q);
}

//----------------------------------------------------------------------------------------------------

bool Math::PointInRect(const Vector2& point, const Rect& rect)
{
	if (point.x > rect.right || point.x < rect.left ||
		point.y > rect.bottom || point.y < rect.top)
	{
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::PointInCircle(const Vector2& point, const Circle& circle)
{
	const Vector2 centerToPoint = point - circle.center;
	const float distSqr = Dot(centerToPoint, centerToPoint);
	const float radiusSqr = circle.radius * circle.radius;
	return distSqr < radiusSqr;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const LineSegment& a, const LineSegment& b)
{
	// http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/

	float ua = ((a.to.x - a.from.x) * (b.from.y - a.from.y)) - ((a.to.y - a.from.y) * (b.from.x - a.from.x));
	float ub = ((b.to.x - b.from.x) * (b.from.y - a.from.y)) - ((b.to.y - b.from.y) * (b.from.x - a.from.x));
	float denom = ((a.to.y - a.from.y) * (b.to.x - b.from.x)) - ((a.to.x - a.from.x) * (b.to.y - b.from.y));

	// First check for special cases
	if (denom == 0.0f)
	{
		if (ua == 0.0f && ub == 0.0f)
		{
			// The line segments are the same
			return true;
		}
		else
		{
			// The line segments are parallel
			return false;
		}
	}

	ua /= denom;
	ub /= denom;

	if (ua < 0.0f || ua > 1.0f || ub < 0.0f || ub > 1.0f)
	{
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Circle& c0, const Circle& c1)
{
	const float totalRadius = c0.radius + c1.radius;
	const float totalRadiusSquare = totalRadius * totalRadius;
	const float fDistanceSquared = DistanceSqr(c0.center, c1.center);
	return (fDistanceSquared < totalRadiusSquare);
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Rect& r0, const Rect& r1)
{
	if (r0.left > r1.right)
		return false;
	else if (r0.top > r1.bottom)
		return false;
	else if (r0.right < r1.left)
		return false;
	else if (r0.bottom < r1.top)
		return false;
	return true;
}
//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const AABB2D& aabb0, const AABB2D& aabb1)
{
	if (aabb0.Xmin > aabb1.Xmax)
		return false;
	else if (aabb0.Ymin > aabb1.Ymax)
		return false;
	else if (aabb0.Xmax < aabb1.Xmin)
		return false;
	else if (aabb0.Ymax < aabb1.Ymin)
		return false;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const LineSegment& l, const Circle& c)
{
	return Intersect(c, l);
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Circle& c, const LineSegment& l)
{
	Vector2 startToCenter = c.center - l.from;
	Vector2 startToEnd = l.to - l.from;
	float len = Magnitude(startToEnd);
	Vector2 dir = startToEnd / len;

	// Find the closest point to the line segment
	float projection = Dot(startToCenter, dir);
	Vector2 closestPoint;
	if (projection > len)
	{
		closestPoint = l.to;
	}
	else if (projection < 0.0f)
	{
		closestPoint = l.from;
	}
	else
	{
		closestPoint = l.from + (dir * projection);
	}

	// Check if the closest point is within the circle
	Vector2 closestToCenter = c.center - closestPoint;
	if (MagnitudeSqr(closestToCenter) > Sqr(c.radius))
	{
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Circle& c, const Rect& r)
{
	return Intersect(r, c);
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Rect& r, const Circle& c)
{
	Vector2 closestPoint;
	closestPoint.x = Clamp(c.center.x, r.left, r.right);
	closestPoint.y = Clamp(c.center.y, r.top, r.bottom);

	const float distance = Distance(closestPoint, c.center);
	if (distance > c.radius)
	{
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance)
{
	// Reference: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

	// Find vectors for two edges sharing V1
	Vector3 e1 = b - a;
	Vector3 e2 = c - a;

	// Begin calculating determinant - also used to calculate u parameter
	Vector3 P = Cross(ray.dir, e2);

	// If determinant is near zero, ray lies in plane of triangle
	float det = Dot(e1, P);
	// NOT CULLING
	if (IsZero(det))
	{
		return false;
	}

	float inv_det = 1.0f / det;

	// Calculate distance from V1 to ray origin
	Vector3 T = ray.org - a;

	// Calculate u parameter and test bound
	float u = Dot(T, P) * inv_det;

	// The intersection lies outside of the triangle
	if (u < 0.0f || u > 1.0f)
	{
		return false;
	}

	// Prepare to test v parameter
	Vector3 Q = Cross(T, e1);

	// Calculate V parameter and test bound
	float v = Dot(ray.dir, Q) * inv_det;

	// The intersection lies outside of the triangle
	if (v < 0.0f || u + v  > 1.0f)
	{
		return false;
	}

	// Ray intersection
	float t = Dot(e2, Q) * inv_det;
	if (t <= 0.0f)
	{
		// No hit, no win
		return false;
	}

	distance = t;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Ray& ray, const Plane& plane, float& distance)
{
	const float orgDotN = Dot(ray.org, plane.n);
	const float dirDotN = Dot(ray.dir, plane.n);

	// Check if ray is parallel to the plane
	if (IsZero(dirDotN))
	{
		if (IsZero(orgDotN - plane.d))
		{
			distance = 0.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	// Compute distance
	distance = (plane.d - orgDotN) / dirDotN;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Ray& ray, const AABB& aabb, float& distEntry, float& distExit)
{
	// https://truesculpt.googlecode.com/hg-history/Release%25200.8/Doc/ray_box_intersect.pdf

	// Returns true if ray intersects bounding box
	// Sets d1 to entry distance, d2 to exit distance (along ray.dir)

	Vector3 boxMin = aabb.center - aabb.extend;
	Vector3 boxMax = aabb.center + aabb.extend;
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	float divx = 1.0f / ray.dir.x;
	float divy = 1.0f / ray.dir.y;
	float divz = 1.0f / ray.dir.z;

	if (divx >= 0.0f)
	{
		tmin = (boxMin.x - ray.org.x) * divx;
		tmax = (boxMax.x - ray.org.x) * divx;
	}
	else
	{
		tmin = (boxMax.x - ray.org.x) * divx;
		tmax = (boxMin.x - ray.org.x) * divx;
	}
	if (divy >= 0.0f)
	{
		tymin = (boxMin.y - ray.org.y) * divy;
		tymax = (boxMax.y - ray.org.y) * divy;
	}
	else
	{
		tymin = (boxMax.y - ray.org.y) * divy;
		tymax = (boxMin.y - ray.org.y) * divy;
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	if (divz >= 0.0f)
	{
		tzmin = (boxMin.z - ray.org.z) * divz;
		tzmax = (boxMax.z - ray.org.z) * divz;
	}
	else
	{
		tzmin = (boxMax.z - ray.org.z) * divz;
		tzmax = (boxMin.z - ray.org.z) * divz;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	distEntry = tmin;
	distExit = tmax;
	return true;
}

//----------------------------------------------------------------------------------------------------

//bool Math::Intersect(const Ray& ray, const OBB& obb, float& distEntry, float& distExit)
//{
//	// Compute the local-to-world/world-to-local matrices
//	Matrix4 matTrans = Matrix4::Translation(obb.center.x, obb.center.y, obb.center.z);
//	Matrix4 matRot = MatrixRotationQuaternion(obb.orientation);
//	Matrix4 matWorld = matRot * matTrans;
//	Matrix4 matWorldInv = Inverse(matWorld);
//
//	// Transform the ray into the OBB's local space
//	Vector3 org = TransformCoord(ray.org, matWorldInv);
//	Vector3 dir = TransformNormal(ray.dir, matWorldInv);
//
//	AABB aabb(Vector3::Zero(), obb.extend);
//	return Math::Intersect(Ray(org, dir), aabb, distEntry, distExit);
//}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Vector3& point, const AABB& aabb)
{
	const Vector3 test = point - aabb.center;
	if (abs(test.x) > aabb.extend.x) return false;
	if (abs(test.y) > aabb.extend.y) return false;
	if (abs(test.z) > aabb.extend.z) return false;
	return true;
}

//----------------------------------------------------------------------------------------------------

//bool Math::Intersect(const Vector3& point, const OBB& obb)
//{
//	// Compute the local-to-world/world-to-local matrices
//	Matrix4 matTrans = Matrix4::Translation(obb.center.x, obb.center.y, obb.center.z);
//	Matrix4 matRot = MatrixRotationQuaternion(obb.orientation);
//	Matrix4 matWorld = matRot * matTrans;
//	Matrix4 matWorldInv = Inverse(matWorld);
//
//	// Transform the point into the OBB's local space
//	Vector3 localPoint = TransformCoord(point, matWorldInv);
//	AABB aabb(Vector3::Zero(), obb.extend);
//
//	// Test against local AABB
//	return Math::Intersect(localPoint, aabb);
//}
//----------------------------------------------------------------------------------------------------

Rect Math::GetAABB2DIntersectionRect(const AABB2D& aabb0, const AABB2D& aabb1)
{
	Rect intersection;

	intersection.left = Max(aabb0.Xmin, aabb1.Xmin);
	intersection.top = Max(aabb0.Ymin, aabb1.Ymin);
	intersection.right = Min(aabb0.Xmax, aabb1.Xmax);
	intersection.bottom = Min(aabb0.Ymax, aabb1.Ymax);

	return intersection;
}

Math::Vector3 Math::GetClosestPoint(const Ray& ray, const Vector3& point)
{
	Vector3 orgToPoint = point - ray.org;
	float d = Dot(orgToPoint, ray.dir);
	return ray.org + (ray.dir * d);
}

//----------------------------------------------------------------------------------------------------

Math::Vector3 Math::Mean(const Vector3* v, uint32_t count)
{
	Vector3 mean(0.0f, 0.0f, 0.0f);
	for (uint32_t i = 0; i < count; ++i)
	{
		mean += v[i];
	}
	return mean / (float)count;
}

float Math::RandomFloat(float min, float max)
{
	//srand(time(NULL));
	// this  function assumes max > min, you may want 
	// more robust error checking for a non-debug build
	assert(max > min, "[Math] Invalid parameters. Max should be greater than Min.");
	float random = ((float)rand()) / (float)RAND_MAX;

	// generate (in your case) a float between 0 and (4.5-.78)
	// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random * range) + min;
}

int Math::RandomInt(int min, int max)
{
	//srand(time(NULL));
	assert(max > min, "[Math] Invalid parameters. Max should be greater than Min.");
	return rand() % max + min;
}

Math::Vector3 Math::VecMax(const Vector3& a, const Vector3& b)
{
	Vector3 result;
	result = { std::max(a.x, b.x), std::max(a.y, b.y) , std::max(a.z, b.z) };
	return result;
}

Math::Vector3 Math::VecMin(const Vector3& a, const Vector3& b)
{
	Vector3 result;
	result = { std::min(a.x, b.x), std::min(a.y, b.y) , std::min(a.z, b.z) };
	return result;
}