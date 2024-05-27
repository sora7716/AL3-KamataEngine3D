#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>
static const int kRowHeight   = 20;
static const int kColumnWidth = 60;
class ScreenPrintf{
public:
	/// <summary>
	/// マトリックスのスクリーンプリント
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="matrix">表示したいマトリックス</param>
	/// <param name="type">名前</param>
	static void MatrixScreenPrintf(int x, int y, MyMatrix4x4 matrix, const char* label);

	/// <summary>
	/// ベクトルのスクリーンプリント
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <param name="vector">表示したいベクトル</param>
	/// <param name="label">名前</param>
	static void VectorScreenPrintf(int x, int y, MyVector3 vector, const char* label);
};

