#include "Quaternion.h"

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result{};
	result.w = (lhs.w * rhs.w) - (Dot(lhs.vec, rhs.vec));
	result.vec = (Cross(lhs.vec, rhs.vec)) + (rhs.w * lhs.vec) + (lhs.w * rhs.vec);
	return result;
}

Quaternion IdentityQuaternion()
{
	Quaternion result{};
	result.w = 1.0f;
	result.vec = 0.0f * result.vec;

	return result;
}

Quaternion Conjugate(const Quaternion& quaternion)
{
	Quaternion result{};
	result.vec = -1.0f * quaternion.vec;
	result.w = 1.0f;
	return result;
}

float Norm(const Quaternion& quaternion)
{
	float result{};
	result = sqrtf(quaternion.vec.x * quaternion.vec.x +
		quaternion.vec.y * quaternion.vec.y +
		quaternion.vec.z * quaternion.vec.z +
		quaternion.w * quaternion.w);
	return result;
}

Quaternion QNormalize(const Quaternion& quaternion)
{
	Quaternion result{};
	result.vec = quaternion.vec / Norm(quaternion);
	result.w = quaternion.w / Norm(quaternion);

	return result;
}

Quaternion QInverse(const Quaternion& quaternion)
{
	Quaternion result{};
	float n = Norm(quaternion) * Norm(quaternion);
	result = Conjugate(quaternion) / n;

	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	Quaternion result;
	result.vec.x = axis.x * std::sinf(angle / 2.0f);
	result.vec.y = axis.y * std::sinf(angle / 2.0f);
	result.vec.z = axis.z * std::sinf(angle / 2.0f);
	result.w = std::cosf(angle / 2.0f);

}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Vector3 result;
	Quaternion n;
	n.vec.x = vector.x;
	n.vec.y = vector.y;
	n.vec.z = vector.z;
	n.w = Length(vector);

	Quaternion a = Multiply(Multiply(quaternion, n), Conjugate(quaternion));

	result.x = a.vec.x;
}

Vector3 operator+(const Vector3& a, const Vector3& b) {
	Vector3 c = { a.x + b.x,a.y + b.y ,a.z + b.z };

	return c;
}

Vector3 operator+(const Vector3& a, const float& b) {
	Vector3 c = { a.x + b,a.y + b,a.z + b };

	return c;
}

Vector3 operator-(const Vector3& a, const Vector3& b) {
	Vector3 c = { a.x - b.x,a.y - b.y,a.z - b.z };

	return c;
}

Vector3 operator-(const Vector3& a, const float& b) {
	Vector3 c = { a.x - b,a.y - b,a.z - b };

	return c;
}

Vector3 operator*(const Vector3& a, const Vector3& b) {
	Vector3 c = { a.x * b.x, a.y * b.y, a.z * b.z };

	return c;
}

Vector3 operator*(const float& a, const Vector3& b) {
	Vector3 c = { a * b.x,a * b.y,a * b.z };

	return c;
}

Vector3 operator/(const Vector3& a, const float& b)
{
	Vector3 c = { a.x / b , a.y / b, a.z / b };

	return c;
}

Quaternion operator/(const Quaternion& q, const float& a)
{
	Quaternion result{};
	result.vec = q.vec / a;
	result.w = q.w / a;
	return result;
}

Vector3 operator*(const Vector3& vec, const Matrix4x4& mat) {
	Vector4 result = {
		vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0],
		vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1],
		vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2],
		vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + mat.m[3][3]
	};

	return { result.x / result.w, result.y / result.w, result.z / result.w };
}
