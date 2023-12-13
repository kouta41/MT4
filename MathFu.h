#include <Novice.h>
#include <Vector3.h>
#include <Vector4.h>
#define _USE_MATH_DEFINES
#include <Math.h>
#include <Matrix4x4.h>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <assert.h>

//struct Sphere {
//	Vector3 center;
//	float radius;
//};
//
//struct Line {
//	Vector3 origin;//始点
//	Vector3 diff;//終点への差分ベクトル
//};
//struct Ray {
//	Vector3 origin;//始点
//	Vector3 diff;//終点への差分ベクトル
//};
//struct Segment {
//	Vector3 origin;//始点
//	Vector3 diff;//終点への差分ベクトル
//};
//
//struct Plane {
//	Vector3 normal;//法線
//	float distance;//距離
//};
//
//struct TriAngle {
//	Vector3 vertices[3];//頂点
//};
//
//struct AABB {
//	Vector3 min;//!<最小点
//	Vector3 max;//!<最大点
//};

Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const float& f1);
float Length(const Vector3& v);
Vector3 Transforme(const Vector3& vector, const Matrix4x4& matrix);
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
//void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);

Vector3 Multiply(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
Vector3 Normalize(const Vector3& v1);
Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
Vector3 Project(const Vector3& v1, const Vector3& v2);
//Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
//Vector3 Perpendicular(const Vector3& vector);
//void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);
//bool IsCollision(const Sphere& s1, const Plane& p1);
//bool IsCollision(const Sphere& s1, const Sphere& s2);
//bool IsCollision(const Segment& segment, const Plane& plane);
//void DrawTriAngle(const TriAngle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);
//bool IsCollision(const Segment& segment, const TriAngle& triangle);
//bool IsCollision(const AABB& aabb1, const AABB& aabb2);
//void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//bool IsCollision(const AABB& aabb1, const Sphere& s1);