#pragma once
#include"asset/math/Aithmetic.h"
#include"WorldTransform.h"

//前方宣言
class Model;
class ViewProjection;

/// <summary>
/// プレイヤーのバレットクラス
/// </summary>
class PlayerBullet {

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBullet() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model,const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

private://メンバ変数
	Model* model_=nullptr;//モデル
	WorldTransform worldTransform_;//ワールドトランスフォーム
	uint32_t texture_ = 0u;//テクスチャ
};
