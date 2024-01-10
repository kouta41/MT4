#pragma once
#include <Vector3.h>
#include <Vector4.h>
#include <iostream>
#include <cassert>
#include "MathFu.h"

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};


// quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
// 単位quaternion
Quaternion IdentityQuaternion();
// 共役quaternion
Quaternion Conjugate(const Quaternion& quaternion);
// quaternionのnorm
float Norm(const Quaternion& quaternion);
// 正規化したquaternion
Quaternion QNormalize(const Quaternion& quaternion);
// 逆quaternion
Quaternion QInverse(const Quaternion& quaternion);

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);


Matrix4x4  MakeRotateMatrix(const Quaternion& quaternion);

