#pragma once
#include <vector>
#include "WorldTransform.h"
using namespace std;

//前方宣言
class ViewProjection;
class Model;
class MapChipField;

class Blocks {

public://メンバ関数
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

private://メンバ変数
	Model* model_ = nullptr;                               // モデル
	MapChipField* mapChipField_ = nullptr;                 // マップチップフィールド
	uint32_t texture_ = 0u;                                // テクスチャ
	ViewProjection* viewProjection_ = nullptr;             // ビュープロジェクション
	vector<vector<WorldTransform*>> worldTransformBlocks_; // ワールドトランスフォーム



};
