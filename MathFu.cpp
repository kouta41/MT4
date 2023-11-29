#include "MathFu.h"

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return Vector3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
Vector3 Subtract(const Vector3& v1, const float& f1) {
	return Vector3{ v1.x - f1, v1.y - f1, v1.z - f1 };
}
float Length(const Vector3& v) {
	return sqrtf(Dot(v, v));
}

Vector3 Transforme(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

// 回転行列
Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2) {
	Matrix4x4 m4;
	m4.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
		m1.m[0][3] * m2.m[3][0];
	m4.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
		m1.m[0][3] * m2.m[3][1];
	m4.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
		m1.m[0][3] * m2.m[3][2];
	m4.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
		m1.m[0][3] * m2.m[3][3];

	m4.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
		m1.m[1][3] * m2.m[3][0];
	m4.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
		m1.m[1][3] * m2.m[3][1];
	m4.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
		m1.m[1][3] * m2.m[3][2];
	m4.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
		m1.m[1][3] * m2.m[3][3];

	m4.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
		m1.m[2][3] * m2.m[3][0];
	m4.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
		m1.m[2][3] * m2.m[3][1];
	m4.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
		m1.m[2][3] * m2.m[3][2];
	m4.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
		m1.m[2][3] * m2.m[3][3];

	m4.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
		m1.m[3][3] * m2.m[3][0];
	m4.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
		m1.m[3][3] * m2.m[3][1];
	m4.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
		m1.m[3][3] * m2.m[3][2];
	m4.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
		m1.m[3][3] * m2.m[3][3];
	return m4;
}

Vector3 Multiply(float scalar, const Vector3& v) {
	return { v.x * scalar,v.y * scalar,v.z * scalar };
}
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 Cross;
	Cross.x = v1.y * v2.z - v1.z * v2.y;
	Cross.y = v1.z * v2.x - v1.x * v2.z;
	Cross.z = v1.x * v2.y - v1.y * v2.x;
	return Cross;
}
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfwidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfwidth * 2.0f) / float(kSubdivision);
	Vector3 worldVerticles[2];
	Vector3 screenVerticles[2];
	Vector3 ndcVertices;
	//横
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		worldVerticles[0] = { kGridEvery * xIndex - kGridHalfwidth,0.0f,kGridHalfwidth };
		worldVerticles[1] = { kGridEvery * xIndex - kGridHalfwidth,0.0f,-kGridHalfwidth };
		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertices = Transforme(worldVerticles[i], viewProjectionMatrix);
			screenVerticles[i] = Transforme(ndcVertices, viewportMatrix);
		}
		Novice::DrawLine((int)screenVerticles[0].x, (int)screenVerticles[0].y, (int)screenVerticles[1].x, (int)screenVerticles[1].y, 0x0000FF);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		worldVerticles[0] = { kGridHalfwidth,0.0f,kGridEvery * zIndex - kGridHalfwidth };
		worldVerticles[1] = { -kGridHalfwidth,0.0f, kGridEvery * zIndex - kGridHalfwidth };

		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertices = Transforme(worldVerticles[i], viewProjectionMatrix);
			screenVerticles[i] = Transforme(ndcVertices, viewportMatrix);
		}
		Novice::DrawLine((int)screenVerticles[0].x, (int)screenVerticles[0].y, (int)screenVerticles[1].x, (int)screenVerticles[1].y, 0x000000FF);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {
	const uint32_t kSubDivision = 30;
	const float kLonEvery = 2.0f * (float)M_PI / float(kSubDivision);
	const float kLatEvery = (float)M_PI / float(kSubDivision);

	for (uint32_t latIndex = 0; latIndex < kSubDivision; ++latIndex) {
		float lat = -1.0f * (float)M_PI / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubDivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;

			Vector3 a, b, c;
			a = { sphere.radius * std::cosf(lat) * std::cosf(lon), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon) };
			a = Add(a, sphere.center);
			b = { sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon), sphere.radius * std::sinf(lat + kLatEvery), sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon) };
			b = Add(b, sphere.center);
			c = { sphere.radius * std::cosf(lat) * std::cosf(lon + kLonEvery), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery) };
			c = Add(c, sphere.center);

			a = Transforme(a, viewProjectionMatrix);
			a = Transforme(a, viewportMatrix);
			b = Transforme(b, viewProjectionMatrix);
			b = Transforme(b, viewportMatrix);
			c = Transforme(c, viewProjectionMatrix);
			c = Transforme(c, viewportMatrix);


			Novice::DrawLine(
				int(a.x), int(a.y),
				int(b.x), int(b.y),
				color
			);

			Novice::DrawLine(
				int(a.x), int(a.y),
				int(c.x), int(c.y),
				color
			);

		}
	}

};

float Dot(const Vector3& v1, const Vector3& v2) {
	float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}

Vector3 Normalize(const Vector3& v1) {
	Vector3 Result = v1;
	float length = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	Result.x /= length;
	Result.y /= length;
	Result.z /= length;
	return Result;
}

//正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result = Multiply(Dot(v1, Normalize(v2)), Normalize(v2));
	return result;
}
//最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	float length = sqrt(segment.diff.x * segment.diff.x + segment.diff.y * segment.diff.y + segment.diff.z * segment.diff.z);
	Vector3 normaliseSegment = { segment.diff.x / length,segment.diff.y / length,segment.diff.z / length };

	float distance = Dot(Subtract(point, segment.origin), normaliseSegment);
	distance = std::clamp(distance, 0.0f, length);
	Vector3 proj = Multiply(distance, normaliseSegment);
	return Add(segment.origin, proj);
};
Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transforme(Transforme(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[0].x, (int)points[0].y, color);
}
bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(Subtract(s2.center, s1.center));
	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& s1, const Plane& p1) {
	float distance = Dot(Normalize(p1.normal), Subtract(s1.center, p1.distance));
	if (std::abs(distance) <= s1.radius) {
		return true;
	}
	else {
		return false;
	}
}
bool IsCollision(const Segment& segment, const Plane& plane)
{
	float dot = Dot(segment.diff, plane.normal);
	//垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}
	//tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal) / dot);
	//tの値と線の種類によって衝突しているかを判定
	if (0.0f <= t && t <= 1.0f) {
		return true;
	}
	return false;
}

void DrawTriAngle(const TriAngle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color)
{
	Vector3 verticle[3];
	for (int i = 0; i < 3; i++) {
		verticle[i] = Transforme(Transforme(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawTriangle((int)verticle[0].x, (int)verticle[0].y, (int)verticle[1].x, (int)verticle[1].y, (int)verticle[2].x, (int)verticle[2].y, color, kFillModeWireFrame);
}
bool IsCollision(const Segment& segment, const TriAngle& triangle)
{
	//TriAngleから面を作る
	Plane plane{};
	plane.normal =
		Normalize(
			Cross(
				Subtract(triangle.vertices[1], triangle.vertices[0]),
				Subtract(triangle.vertices[2], triangle.vertices[1])
			)
		);

	plane.distance = Dot(triangle.vertices[0], plane.normal);

	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (0.0f < t && t < 1.0f) {
		Vector3 p = Add(segment.origin, Multiply(t, segment.diff));


		Vector3 cross01 = Cross(
			Subtract(triangle.vertices[1], triangle.vertices[0]),
			Subtract(p, triangle.vertices[1])
		);
		Vector3 cross12 = Cross(
			Subtract(triangle.vertices[2], triangle.vertices[1]),
			Subtract(p, triangle.vertices[2])
		);
		Vector3 cross20 = Cross(
			Subtract(triangle.vertices[0], triangle.vertices[2]),
			Subtract(p, triangle.vertices[0])
		);


		if (Dot(cross01, plane.normal) >= 0.0f &&
			Dot(cross12, plane.normal) >= 0.0f &&
			Dot(cross20, plane.normal) >= 0.0f) {
			return true;
		}

	}

	return false;
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 point[8];
	point[0] = { aabb.min.x, aabb.min.y, aabb.min.z };
	point[1] = { aabb.min.x, aabb.min.y, aabb.max.z };
	point[2] = { aabb.min.x, aabb.max.y, aabb.min.z };
	point[3] = { aabb.max.x, aabb.min.y, aabb.min.z };
	point[4] = { aabb.max.x, aabb.max.y, aabb.min.z };
	point[5] = { aabb.min.x, aabb.max.y, aabb.max.z };
	point[6] = { aabb.max.x, aabb.min.y, aabb.max.z };
	point[7] = { aabb.max.x, aabb.max.y, aabb.max.z };

	Vector3 screenpoint[8]{};
	for (int i = 0; i < 8; i++) {
		point[i] = Transforme(point[i], viewProjectionMatrix);
		screenpoint[i] = Transforme(point[i], viewportMatrix);
	}
	Novice::DrawLine(int(screenpoint[0].x), int(screenpoint[0].y), int(screenpoint[1].x), int(screenpoint[1].y), color);
	Novice::DrawLine(int(screenpoint[0].x), int(screenpoint[0].y), int(screenpoint[2].x), int(screenpoint[2].y), color);
	Novice::DrawLine(int(screenpoint[0].x), int(screenpoint[0].y), int(screenpoint[3].x), int(screenpoint[3].y), color);

	Novice::DrawLine(int(screenpoint[1].x), int(screenpoint[1].y), int(screenpoint[5].x), int(screenpoint[5].y), color);
	Novice::DrawLine(int(screenpoint[1].x), int(screenpoint[1].y), int(screenpoint[6].x), int(screenpoint[6].y), color);

	Novice::DrawLine(int(screenpoint[2].x), int(screenpoint[2].y), int(screenpoint[4].x), int(screenpoint[4].y), color);
	Novice::DrawLine(int(screenpoint[2].x), int(screenpoint[2].y), int(screenpoint[5].x), int(screenpoint[5].y), color);

	Novice::DrawLine(int(screenpoint[3].x), int(screenpoint[3].y), int(screenpoint[4].x), int(screenpoint[4].y), color);
	Novice::DrawLine(int(screenpoint[3].x), int(screenpoint[3].y), int(screenpoint[6].x), int(screenpoint[6].y), color);

	Novice::DrawLine(int(screenpoint[4].x), int(screenpoint[4].y), int(screenpoint[7].x), int(screenpoint[7].y), color);
	Novice::DrawLine(int(screenpoint[5].x), int(screenpoint[5].y), int(screenpoint[7].x), int(screenpoint[7].y), color);
	Novice::DrawLine(int(screenpoint[6].x), int(screenpoint[6].y), int(screenpoint[7].x), int(screenpoint[7].y), color);
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {

		return true;

	}

	return false;

}

bool IsCollision(const AABB& aabb1, const Sphere& s1) {

	Vector3 closestPoint{
		std::clamp(s1.center.x,aabb1.min.x,aabb1.max.x),
		std::clamp(s1.center.y,aabb1.min.y,aabb1.max.y),
		std::clamp(s1.center.z,aabb1.min.z,aabb1.max.z),
	};
	//最近接点と中心の距離を求める
	float distance = Length(Subtract(closestPoint, s1.center));
	//距離が半径よりも小さければ衝突
	if (distance <= s1.radius) {
		return true;
	}
	return false;

}