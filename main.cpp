#include <Novice.h>
#include "Matrix4x4.h"
#include "Vector3.h"


#include "MathFu.h"
#include "Quaternion.h"

const char kWindowTitle[] = "LE2B_18_ツシマコウタ";


static const int kRowHeight = 20;
static const int kColumnWindth = 60;







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


 
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y - kRowHeight, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWindth, y + row * kRowHeight, "%6.03f", matrix.m[row][column]);
		}
	}
}
void QuaternionScreenPrintf(int x, int y, const Quaternion& matrix, const char* label) {
	Novice::ScreenPrintf(x  , y , "%6.02f", matrix.x);
	Novice::ScreenPrintf(x * kColumnWindth, y , "%6.02f", matrix.y);
	Novice::ScreenPrintf(x * kColumnWindth*2, y , "%6.02f", matrix.z);
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
		
		Quaternion rotation0 = MakeRotateAxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
		Quaternion rotation1 = { -rotation0.x,-rotation0.y,-rotation0.z,-rotation0.w };

		Quaternion interpolat0 = Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolat1 = Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolat2 = Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolat3 = Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolat4 = Slerp(rotation0, rotation1, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		QuaternionScreenPrintf(1, 20, interpolat0, "interpolat0");
		QuaternionScreenPrintf(1, 20*2, interpolat1, "interpolat1");
		QuaternionScreenPrintf(1, 20*3, interpolat2, "interpolat2");
		QuaternionScreenPrintf(1, 20*4, interpolat3, "interpolat3");
		QuaternionScreenPrintf(1, 20*5, interpolat4, "interpolat4");

		////Novice::ScreenPrintf(1, 20*7, "%6.02f", norm);
		//Novice::ScreenPrintf(1 * kColumnWindth * 5, 20 * 7, ":Norm");



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
