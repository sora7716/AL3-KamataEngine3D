#pragma once
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "Vector4.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"

/// <summary>
/// 形のクラス
/// </summary>
class Shape {
public: // 構造体
	// AABB
	typedef struct AABB {
		Vector3 min;
		Vector3 max;
	} AABB;

	// 六角形を作るときに使う素材
	typedef struct HexagonMaterial {
		Vector3 rotation = {};             // 回転
		Vector3 center;                    // 中心
		Vector3 size = {1.0f, 1.0f, 1.0f}; // 座標軸方向の長さの半分。中心から面までの距離 scale
		Vector3 normal[4];                 // 法線ベクトル
	} HexagonMaterial;

	// OBBの素材
	typedef struct ObbMaterial {
		Vector3 center; // 中心 translation
		Vector3 orientations[3] = {
		    {1.0f, 0.0f, 0.0f},
		    {0.0f, 1.0f, 0.0f},
		    {0.0f, 0.0f, 1.0f},
		}; // 座標軸。正規化・直行必須 rotation
		Vector3 size = {1.0f, 1.0f, 1.0f}; // 座標軸方向の長さの半分。中心から面までの距離 scale
		Vector3 rotation = {};             // 回転
	} OBBMaterial;

	// AABBを2Dで作るときに使う
	typedef struct Vertex2D {
		Vector3 leftTop;
		Vector3 rightTop;
		Vector3 leftBottom;
		Vector3 rightBottom;
	} Vertex2D;

	// スフィアに使う構造体
	typedef struct SphereMaterial {
		Vector3 center;
		float radius;
		Vector3 rotation;
	} SphereMaterial;

	// 直線
	typedef struct StraightLine {
		Vector3 origin; // 始点
		Vector3 diff;   // 終点への差分ベクトル
	} StraightLine;

	// 半直線
	typedef struct Ray {
		Vector3 origin; // 始点
		Vector3 diff;   // 終点への差分ベクトル
	} Ray;

	// 線分
	typedef struct Segment {
		Vector3 origin; // 始点
		Vector3 diff;   // 終点への差分ベクトル
	} Segment;

	// 頂点
	enum class TriangleVertex {
		kTop,
		kRight,
		kLeft,
		kVertexNum,
	};

	// 三角形の素材
	typedef struct TriangleMaterial {
		Vector3 kLocalVertices_[static_cast<int>(TriangleVertex::kVertexNum)];
		Vector3 center;
		float radian;
		Vector3 size;
		Vector3 normal[4];
	} TriangleMaterial;

	// サーチライトの素材(度数法で設定)
	typedef struct SerchlightMaterial {
		Vector3 center;
		float radius;
		float direction; // 向き(角度)
		float range;     // 範囲(角度)
	} SerchlightMaterial;

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Shape() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Shape() = default;

	/// <summary>
	/// ローカルの頂点を変換
	/// </summary>
	/// <param name="scale">サイズ</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">移動</param>
	/// <param name="kLocalVertex">ローカルの頂点</param>
	/// <returns>変換</returns>
	Vector3 Conversion(const Vector3& scale, const Vector3& rotate, const Vector3& translate, const Vector3& kLocalVertex);

	/// <summary>
	/// ローカルの頂点を変換(scaleが無いver)
	/// </summary>
	/// <param name="rotate">回転</param>
	/// <param name="translate">移動</param>
	/// <param name="kLocalVertex">ローカルの頂点</param>
	/// <returns>変換</returns>
	Vector3 Conversion(const Vector3& rotate, const Vector3& translate, const Vector3& kLocalVertex);

	/// <summary>
	/// OBB用の変換
	/// </summary>
	/// <param name="rotate">回転</param>
	/// <param name="translate">移動</param>
	/// <param name="kLocalVertex">ローカル頂点</param>
	/// <param name="orientations">法線</param>
	/// <returns>変換</returns>
	Vector3 Conversion(const Vector3& rotate, const Vector3& translate, const Vector3& kLocalVertex, Vector3* orientations);

	/// <summary>
	/// OBB用の変換
	/// </summary>
	/// <param name="rotate">回転</param>
	/// <param name="kLocalVertex">ローカル頂点</param>
	/// <param name="orientations">法線</param>
	/// <returns>変換</returns>
	Vector3 Conversion(const Vector3& rotate, const Vector3& kLocalVertex, Vector3* orientations);

	/// <summary>
	/// OBB用の回転行列
	/// </summary>
	/// <param name="orientations">回転行列から抽出するやつ</param>
	/// <param name="rotate">回転する値</param>
	static void MakeOBBRotateMatrix(Vector3* orientations, const Vector3& rotate);

	/// <summary>
	/// OBB用のワールド行列
	/// </summary>
	/// <param name="orientations">回転行列から抽出したやつ</param>
	/// <param name="center">センターの値</param>
	/// <returns>OBBのワールド行列</returns>
	static Matrix4x4 MakeOBBWorldMatrix(const Vector3* orientations, const Vector3 center);

	/// <summary>
	/// OBB用のワールド行列
	/// </summary>
	/// <param name="orientations">回転行列から抽出した法線</param>
	/// <returns>OBBのワールド行列</returns>
	static Matrix4x4 MakeOBBWorldMatrix(const Vector3* orientations);
	/// <summary>
	/// 当たった時の判定
	/// </summary>
	/// <param name="isHit">衝突判定</param>
	void OnCollision(bool isHit);

	// コピーコンストラクタを禁止する
	Shape(const Shape& shape) = delete;

	// 代入演算を禁止する
	const Shape operator=(const Shape& shape) = delete;

protected:                           // メンバ変数
	Matrix4x4 worldMatrix_;          // ワールド行列
	ViewProjection* viewProjection_; // ビュープロジェクション行列
	Vector4 color_ = WHITE;          // 色
	bool isHit_ = false;             // 衝突判定
};
