#pragma once
#include <vector>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "gameObject/mapChipField/MapChipField.h"
using namespace std;
class Blocks {
private:
	Model* model_ = nullptr;//モデル
	MapChipField* mapChipField_ = nullptr;//マップチップフィールド
	uint32_t texture_ = 0u;//テクスチャ
	ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション
	vector<vector<WorldTransform*>> worldTransformBlocks_;//ワールドトランスフォーム


public:
	/// <summary>
	/// ブロックの初期化
	/// </summary>
	/// <param name="model">3Dモデル</param>
	/// <param name="texture">ブロックのテクスチャ</param>
	/// <param name="viewProjection">ブロックのビュープロジェクション</param>
	/// <param name="mapChipField">マップチップフィールド</param>
	void Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection,MapChipField*mapChipField);

	/// <summary>
	/// ブロックの更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// ブロックの描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// worldTransformBlocks_のゲッター
	/// </summary>
	/// <returns>worldTransformBlocks_</returns>
	vector<vector<WorldTransform*>> GetBlocks() { return worldTransformBlocks_; };

};
