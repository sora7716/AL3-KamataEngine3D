#pragma once
#include "Aithmetic.h"
#include "assets/math/easing/Easing.h"

class Math {
public:
	
	/// <summary>
	/// 転置行列
	/// </summary>
	/// <param name="m">マトリック</param>
	/// <returns>matrixの転置行列</returns>
	static Matrix4x4 Transpose(Matrix4x4 m);

	/// <summary>
	/// 単位行列
	/// </summary>
	/// <returns>単位行列</returns>
	static Matrix4x4 MakeIdentity4x4();

	/// <summary>
	/// 拡大縮小
	/// </summary>
	/// <param name="scale">倍率</param>
	/// <returns>倍率のmatrix</returns>
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// 平行移動
	/// </summary>
	/// <param name="translate">移動</param>
	/// <returns>移動のmatrix</returns>
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// 同次座標系で計算し、デカルト座標系で返す
	/// </summary>
	/// <param name="vector">vector</param>
	/// <param name="matrix">matrix</param>
	/// <returns>デカルト座標系</returns>
	static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// x座標を軸に回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>x座標を軸の回転</returns>
	static Matrix4x4 MakeRotateXMatrix(const float& radian);

	/// <summary>
	/// y座標を軸に回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>y座標を軸の回転</returns>
	static Matrix4x4 MakeRotateYMatrix(const float& radian);

	/// <summary>
	/// z座標を軸に回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>z座標を軸の回転</returns>
	static Matrix4x4 MakeRotateZMatrix(const float& radian);

	/// <summary>
	/// x,y,z座標で回転
	/// </summary>
	/// <param name="radian">角度</param>
	/// <returns>回転</returns>
	static Matrix4x4 MakeRotateXYZMatrix(const Vector3& radian);

	/// <summary>
	/// アフィン関数
	/// </summary>
	/// <param name="scale">倍率</param>
	/// <param name="radian">角度</param>
	/// <param name="translate">移動</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate);

	/// <summary>
	/// STRの変換
	/// </summary>
	/// <param name="scale">倍率</param>
	/// <param name="radian">角度</param>
	/// <param name="translate">移動</param>
	/// <returns>STRの変換</returns>
	static Matrix4x4 MakeSTRMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate);

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
	static Matrix4x4 MakeOrthographicMatrix(const float& left, const float& top, const float& right, const float& bottom, const float& nearClip, const float& farClip);

	/// <summary>
	/// 透視投影行列
	/// </summary>
	/// <param name="fovY">画角</param>
	/// <param name="aspectRation">アスペクト比</param>
	/// <param name="nearClip">近平面への距離</param>
	/// <param name="farClip">遠平面への距離</param>
	/// <returns>PerspectiveFovMatrix</returns>
	static Matrix4x4 MakePerspectiveFovMatrix(const float& fovY, const float& aspectRation, const float& nearClip, const float& farClip);

	/// <summary>
	/// ビューポートmatrix
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="top">上</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="minDepth">最小深度値</param>
	/// <param name="maxDepth">最大深度値</param>
	/// <returns>ViewportMatrix</returns>
	static Matrix4x4 MakeViewportMatrix(const float& left, const float& top, const float& width, const float& height, const float& minDepth, const float& maxDepth);

	/// <summary>
	/// クロス積
	/// </summary>
	/// <param name="v1">vector1</param>
	/// <param name="v2">vector2</param>
	/// <returns></returns>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 内積
	/// </summary>
	/// <param name="v1">vector1</param>
	/// <param name="v2">vector2</param>
	/// <returns></returns>
	static float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	///	ノルム
	/// </summary>
	/// <param name="v">vector</param>
	/// <returns></returns>
	static float Length(const Vector3& v);

	/// <summary>
	/// 単位vector
	/// </summary>
	/// <param name="v">vector</param>
	/// <returns></returns>
	static Vector3 Normalize(const Vector3& v);

	/// <summary>
	/// 正規化
	/// </summary>
	/// <param name="num">数字</param>
	/// <returns></returns>
	static float Normalize(const float& num);

	/// <summary>
	/// トランスフォームノーマル
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="m">マトリックス</param>
	/// <returns></returns>
	static Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

	/// <summary>
	/// 線形補間
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <param name="t">媒介変数</param>
	/// <returns>線形補間</returns>
	static Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

	/// <summary>
	/// 線形補間
	/// </summary>
	/// <param name="num1">数字1</param>
	/// <param name="num2">数字2</param>
	/// <param name="t">媒介変数</param>
	/// <returns>線形補間</returns>
	static float Lerp(const float& num1, const float& num2, float t);

	/// <summary>
	/// 球面線形補間
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	/// <param name="t">媒介変数</param>
	/// <returns> 球面線形補間</returns>
	static Vector3 SLerp(const Vector3& v1, const Vector3& v2, float t);

	/// <summary>
	/// CatmullRom補間
	/// </summary>
	/// <param name="p0">点0の座標</param>
	/// <param name="p1">点1の座標</param>
	/// <param name="p2">点2の座標</param>
	/// <param name="p3">点3の座標</param>
	/// <param name= "t">点 1を0.0f点2を1.0fとした割合指定</param>
	/// <returns>CatmullRom補間</returns>
	static Vector3 CatmullRomInterpolation(const Vector3& p0,const Vector3& p1,const Vector3& p2,const Vector3& p3,float t);

	/// <summary>
	/// CatmullRomスプライン曲線上の座標を得る
	/// </summary>
	/// <param name="points">制御点の集合</param>
	/// <param name="t">スプラインの全区間の中での割合指定[0,1]</param>
	/// <returns>CatmullRomスプライン曲線上</returns>
	static Vector3 CatmullRomPosition(const std::vector<Vector3>& points, float t);

	/// <summary>
	/// 三次元のベジエ曲線
	/// </summary>
	/// <param name="p0">始点</param>
	/// <param name="p1">中点</param>
	/// <param name="p2">終点</param>
	/// <param name="t">フレーム</param>
	/// <returns>ベジエ曲線</returns>
	static Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);

	/// <summary>
	/// 三次元ベジエ曲線(球面線形補間ver)
	/// </summary>
	/// <param name="p0">始点</param>
	/// <param name="p1">中点</param>
	/// <param name="p2">終点</param>
	/// <param name="t">フレーム</param>
	/// <returns>ベジエ曲線</returns>
	static Vector3 BezierS(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);

	/// <summary>
	/// 六角形の角の計算
	/// </summary>
	/// <param name="center">中心</param>
	/// <param name="size">サイズ</param>
	/// <returns></returns>
	static vector<Vector2> HexagonVertices(Vector2 center, float size);
};