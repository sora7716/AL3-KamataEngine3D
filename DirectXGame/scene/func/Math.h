#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>
class Math {
public:
	
	/// <summary>
	/// コンストラクター
	/// </summary>
	Math();

	/// <summary>
	/// デストラクター
	/// </summary>
	~Math();

	/// <summary>
	/// 足し算
	/// </summary>
	/// <param name="m1">マトリックス1</param>
	/// <param name="m2">マトリックス2</param>
	/// <returns>2つのマトリックスの和</returns>
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 引き算
	/// </summary>
	/// <param name="m1">マトリックス1</param>
	/// <param name="m2">マトリックス2</param>
	/// <returns>2つのマトリックスの差</returns>
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 掛け算
	/// </summary>
	/// <param name="m1">マトリックス1</param>
	/// <param name="m2">マトリックス2</param>
	/// <returns>2つのマトリックスの積</returns>
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="m">マトリックス</param>
	/// <returns>マトリックスの逆行列</returns>
	static Matrix4x4 Inverse(const Matrix4x4& m);

	/// <summary>
	/// 転置行列
	/// </summary>
	/// <param name="m">マトリック</param>
	/// <returns>マトリックスの転置行列</returns>
	static Matrix4x4 Transpose(const Matrix4x4& m);

	/// <summary>
	/// 単位行列
	/// </summary>
	/// <returns>単位行列</returns>
	static Matrix4x4 MakeIdentity4x4();

	/// <summary>
	/// 拡大縮小
	/// </summary>
	/// <param name="scale">倍率</param>
	/// <returns>倍率のマトリックス</returns>
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// 平行移動
	/// </summary>
	/// <param name="translate">移動</param>
	/// <returns>移動のマトリックス</returns>
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// 同次座標系で計算し、デカルト座標系で返す
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <param name="matrix">マトリックス</param>
	/// <returns>デカルト座標系</returns>
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// x座標を軸に回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>x座標を軸の回転</returns>
	static Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// y座標を軸に回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>y座標を軸の回転</returns>
	static Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// z座標を軸に回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>z座標を軸の回転</returns>
	static Matrix4x4 MakeRotateZMatrix(float radian);

	/// <summary>
	/// x,y,z座標で回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>回転</returns>
	static Matrix4x4 MakeRotateXYZMatrix(Vector3 radian);

	/// <summary>
	/// アフィン関数
	/// </summary>
	/// <param name="scale">倍率</param>
	/// <param name="radian">角度</param>
	/// <param name="translate">移動</param>
	/// <returns>SRT</returns>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate);

	/// <summary>
	/// 正射影行列
	/// </summary>
	/// <param name="left">画面の左端</param>
	/// <param name="top">画面の上端</param>
	/// <param name="right">画面の右端</param>
	/// <param name="bottom">画面の下端</param>
	/// <param name="nearClip">近平面</param>
	/// <param name="farClip">遠平面</param>
	/// <returns>OrthographicMatrix</returns>
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	/// <summary>
	/// 透視投影行列
	/// </summary>
	/// <param name="fovY">画角</param>
	/// <param name="aspectRation">アスペクト比</param>
	/// <param name="nearClip">近平面への距離</param>
	/// <param name="farClip">遠平面への距離</param>
	/// <returns>PerspectiveFovMatrix</returns>
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRation, float nearClip, float farClip);

	/// <summary>
	/// ビューポートマトリックス
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="top">上</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="minDepth">最小深度値</param>
	/// <param name="maxDepth">最大深度値</param>
	/// <returns>ViewportMatrix</returns>
	static Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
};