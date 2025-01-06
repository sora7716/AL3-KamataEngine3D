#pragma once
#include "assets/gameManager/scene/game/battle/gameObject/environment/IEnvironment.h"
#include "cell/BaseCell.h"

// 前方宣言
class MapChipField;

/// <summary>
///// 六角形
/// </summary>
class Honeycomb : public IEnvironment {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Honeycomb(MapChipField* mapChipField);

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
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ワイヤーモデルの表示
	/// </summary>
	void DrawWire() override;

private:                                                        // メンバ変数
	std::vector<std::vector<WorldTransform*>> worldTransforms_; // ワールドトランスフォーム
	int numPieces = 0;                                          // ピースの数
	MapChipField* mapChipField_ = nullptr;                      // マップチップフィールド
	std::vector<std::vector<BaseCell*>> cells_;                 // セル
	WorldTransform collider_;                                   // コライダー用のワールドトランスフォーム
};
