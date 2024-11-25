#pragma once
#include "WorldTransform.h"
#include "assets/math/Aithmetic.h"

// 前方宣言
class Model;
class ViewProjection;
class MapChipField;
/// <summary>
/// 六角形
/// </summary>
class Honeycomb {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Honeycomb() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Honeycomb() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="mapChipField">マップチップフィールド</param>
	void Initialize(Model* model, ViewProjection* viewProjection, MapChipField* mapChipField);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:                                                        // メンバ変数
	Model* model_ = nullptr;                                    // モデル
	ViewProjection* viewProjection_ = nullptr;                  // ビュープロジェクション
	std::vector<std::vector<WorldTransform*>> worldTransforms_; // ワールドトランスフォーム
	WorldTransform* parent_;                                    // 六角形の親
	int numPieces = 0;                                          // ピースの数
	MapChipField* mapChipField_ = nullptr;                      // マップチップフィールド
};
