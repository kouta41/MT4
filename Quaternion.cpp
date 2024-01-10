#include "Quaternion.h"

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;

	result.x = lhs.y * rhs.z - lhs.z * rhs.y + rhs.w * lhs.x + lhs.w * rhs.x;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z + rhs.w * lhs.y + lhs.w * rhs.y;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x + rhs.w * lhs.z + lhs.w * rhs.z;
	result.w = lhs.w * rhs.w - Dot({ lhs.x,lhs.y ,lhs.z }, { rhs.x,rhs.y ,rhs.z });

	return result;
}

Quaternion IdentityQuaternion()
{
	Quaternion result;
	result.x *= 0.0f;
	result.y *= 0.0f;
	result.z *= 0.0f;
	result.w *= 1.0f;
	return result;
}

Quaternion Conjugate(const Quaternion& quaternion)
{
	Quaternion result = quaternion;

	result.x *= -1.0f;
	result.y *= -1.0f;
	result.z *= -1.0f;
	result.w *= 1.0f;

	return result;
}

float Norm(const Quaternion& quaternion)
{
	float result{};
	result = sqrtf(quaternion.x * quaternion.x +
		quaternion.y * quaternion.y +
		quaternion.z * quaternion.z +
		quaternion.w * quaternion.w);
	return result;
}

Quaternion QNormalize(const Quaternion& quaternion)
{
	Quaternion result;
	float len = 1 / sqrtf(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w);
	result = { quaternion.x * len,quaternion.y * len,quaternion.z * len,quaternion.w * len };
	return result;
}

Quaternion QInverse(const Quaternion& quaternion)
{
	Quaternion result;

	float n = Norm(quaternion) * Norm(quaternion);
	Quaternion result2 = Conjugate(quaternion);


	result.x = result2.x / n;
	result.y = result2.y / n;
	result.z = result2.z / n;
	result.w = result2.w / n;

	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	Quaternion result;

	result.x = axis.x * std::sinf(angle / 2.0f);
	result.y = axis.y * std::sinf(angle / 2.0f);
	result.z = axis.z * std::sinf(angle / 2.0f);
	result.w = std::cosf(angle / 2.0f);

	return result;

}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Vector3 result;
	Quaternion n;
	n.x = vector.x;
	n.y = vector.y;
	n.z = vector.z;
	n.w = 0.0f;

	Quaternion a = Multiply(Multiply(quaternion, n), Conjugate(quaternion));

	result.x = a.x;
	result.y = a.y;
	result.z = a.z;

	return result;
}

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion)
{
	Matrix4x4 result;

	result.m[0][0] = (quaternion.w * quaternion.w) + (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[0][1] = 2.0f * ((quaternion.x * quaternion.y) + (quaternion.w * quaternion.z));
	result.m[0][2] = 2.0f * ((quaternion.x * quaternion.z) - (quaternion.w * quaternion.y));
	result.m[0][3] = 0.0f;

	result.m[1][0] = 2.0f * ((quaternion.x * quaternion.y) - (quaternion.w * quaternion.z));
	result.m[1][1] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	result.m[1][2] = 2.0f * ((quaternion.y * quaternion.z) + (quaternion.w * quaternion.x));
	result.m[1][3] = 0.0f;

	result.m[2][0] = 2.0f * ((quaternion.x * quaternion.z) + (quaternion.w * quaternion.y));
	result.m[2][1] = 2.0f * ((quaternion.y * quaternion.z) - (quaternion.w * quaternion.x));
	result.m[2][2] = (quaternion.w * quaternion.w) - (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}


