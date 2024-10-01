#pragma once
#include "WorldTransform.h"
#include <vector>

//前方宣言
class Model;
class ViewProjection;

/// <summary>
/// 六角形
/// </summary>
class Hexagon {
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Hexagon() = default;
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Hexagon() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model,ViewProjection* viewProjection);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public://静的メンバ変数
	static inline const int row = 8;//行
	static inline const int col = 5;//列

private://メンバ変数
	Model* model_ = nullptr; // モデル
	ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション
	std::vector<WorldTransform*> worldTransforms_;    // ワールドトランスフォーム
	float radius_ = 2.0f;//半径
};
