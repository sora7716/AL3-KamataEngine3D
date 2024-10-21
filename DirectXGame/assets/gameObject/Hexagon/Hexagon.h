#pragma once
#include "WorldTransform.h"
#include "assets/math/Aithmetic.h"

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
	static inline const int col = 8;//列

private://メンバ変数
	Model* model_ = nullptr; // モデル
	ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション
	std::vector<std::vector<WorldTransform*>> worldTransforms_; // ワールドトランスフォーム
	WorldTransform *parent_;//六角形の親
	Polar polar_ = {};//極座標に使用する
	int numPieces = 0;//ピースの数
};
