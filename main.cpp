#include <Novice.h>
#include "Matrix4x4.h"
#include "Vector3.h"


#include "MathFu.h"
#include "Quaternion.h"

const char kWindowTitle[] = "LE2B_18_ツシマコウタ";


static const int kRowHeight = 20;
static const int kColumnWindth = 60;





//任意軸回転行列
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {
	Matrix4x4 MakeRotateAxisAngle;
	MakeRotateAxisAngle.m[0][0] = (axis.x * axis.x) * (1 - std::cosf(angle)) + std::cosf(angle);
	MakeRotateAxisAngle.m[0][1] = (axis.x * axis.y) * (1 - std::cosf(angle)) + axis.z * std::sinf(angle);
	MakeRotateAxisAngle.m[0][2] = (axis.x * axis.z) * (1 - std::cosf(angle)) - axis.y * std::sinf(angle);
	MakeRotateAxisAngle.m[0][3] = 0;

	MakeRotateAxisAngle.m[1][0] = (axis.x * axis.y) * (1 - std::cosf(angle)) - axis.z * std::sinf(angle);
	MakeRotateAxisAngle.m[1][1] = (axis.y * axis.y) * (1 - std::cosf(angle)) + std::cosf(angle);
	MakeRotateAxisAngle.m[1][2] = (axis.y * axis.z) * (1 - std::cosf(angle)) + axis.x * std::sinf(angle);
	MakeRotateAxisAngle.m[1][3] = 0;

	MakeRotateAxisAngle.m[2][0] = (axis.x * axis.z) * (1 - std::cosf(angle)) + axis.y * std::sinf(angle);
	MakeRotateAxisAngle.m[2][1] = (axis.y * axis.z) * (1 - std::cosf(angle)) - axis.x * std::sinf(angle);
	MakeRotateAxisAngle.m[2][2] = (axis.z * axis.z) * (1 - std::cosf(angle)) + std::cosf(angle);
	MakeRotateAxisAngle.m[2][3] = 0;

	MakeRotateAxisAngle.m[3][0] = 0;
	MakeRotateAxisAngle.m[3][1] = 0;
	MakeRotateAxisAngle.m[3][2] = 0;
	MakeRotateAxisAngle.m[3][3] = 1;
	
	return 	MakeRotateAxisAngle;

}

//任意軸回転行列ver2
Matrix4x4 MakeRotateAxisAngle2(const Vector3& axis,float angleC,float angleS) {
	Matrix4x4 MakeRotateAxisAngle;
	MakeRotateAxisAngle.m[0][0] = (axis.x * axis.x) * (1 - angleC) + angleC;
	MakeRotateAxisAngle.m[0][1] = (axis.x * axis.y) * (1 - angleC) + axis.z * angleS;
	MakeRotateAxisAngle.m[0][2] = (axis.x * axis.z) * (1 - angleC) - axis.y * angleS;
	MakeRotateAxisAngle.m[0][3] = 0;

	MakeRotateAxisAngle.m[1][0] = (axis.x * axis.y) * (1 - angleC) - axis.z * angleS;
	MakeRotateAxisAngle.m[1][1] = (axis.y * axis.y) * (1 - angleC) + angleC;
	MakeRotateAxisAngle.m[1][2] = (axis.y * axis.z) * (1 - angleC) + axis.x * angleS;
	MakeRotateAxisAngle.m[1][3] = 0;

	MakeRotateAxisAngle.m[2][0] = (axis.x * axis.z) * (1 - angleC) + axis.y * angleS;
	MakeRotateAxisAngle.m[2][1] = (axis.y * axis.z) * (1 - angleC) - axis.x * angleS;
	MakeRotateAxisAngle.m[2][2] = (axis.z * axis.z) * (1 - angleC) + angleC;
	MakeRotateAxisAngle.m[2][3] = 0;

	MakeRotateAxisAngle.m[3][0] = 0;
	MakeRotateAxisAngle.m[3][1] = 0;
	MakeRotateAxisAngle.m[3][2] = 0;
	MakeRotateAxisAngle.m[3][3] = 1;

	return 	MakeRotateAxisAngle;

}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {
	Matrix4x4 DirectionToDirection;

	Vector3 cross = Cross(from, to);
	Vector3 n = Cross(from, to);
	if (cross.x == 0 && cross.y == 0&& cross.z == 0) {
		cross = { from.y,-from.x,0 };
	}
	cross = Normalize(cross);

	float angleC = Dot(from,to);
	float angleS = Length(n);

	DirectionToDirection = MakeRotateAxisAngle2(cross, angleC, angleS);

	return DirectionToDirection;
}
 
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y - kRowHeight, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWindth, y + row * kRowHeight, "%6.03f", matrix.m[row][column]);
		}
	}
}
void QuaternionScreenPrintf(int x, int y, const Quaternion& matrix, const char* label) {
	Novice::ScreenPrintf(x  , y , "%6.02f", matrix.vec.x);
	Novice::ScreenPrintf(x * kColumnWindth, y , "%6.02f", matrix.vec.y);
	Novice::ScreenPrintf(x * kColumnWindth*2, y , "%6.02f", matrix.vec.z);
	Novice::ScreenPrintf(x * kColumnWindth*3, y , "%6.02f", matrix.w);
	Novice::ScreenPrintf(x * kColumnWindth * 5, y , ":%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
		Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
		Quaternion identity = IdentityQuaternion();
		Quaternion conji = Conjugate(q1);
		Quaternion inv = QInverse(q1);
		Quaternion normal = QNormalize(q1);
		Quaternion mul1 = Multiply(q1,q2);
		Quaternion mul2 = Multiply(q2, q1);
		float norm = Norm(q1);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		QuaternionScreenPrintf(1, 20, identity, "identity");
		QuaternionScreenPrintf(1, 20*2, conji, "conji");
		QuaternionScreenPrintf(1, 20*3, inv, "inv");
		QuaternionScreenPrintf(1, 20*4, normal, "normal");
		QuaternionScreenPrintf(1, 20*5, mul1, "mul1");
		QuaternionScreenPrintf(1, 20*6, mul2, "mul2");

		//Novice::ScreenPrintf(1, 20*7, "%6.02f", norm);
		Novice::ScreenPrintf(1 * kColumnWindth * 5, 20 * 7, ":Norm");



		//MatrixScreenPrintf(0, kRowHeight* 6, rotateMatrix1, "rotateMatrix1");
		//MatrixScreenPrintf(0, kRowHeight * 11, rotateMatrix2, "rotateMatrix2");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
