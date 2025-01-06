#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#include <memory>
#include "assets/math/collision/shape/hexagon/Hexagon.h"
#include "WorldTransform.h"

/// <summary>
/// セルの基底クラス
/// </summary>
class BaseCell {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseCell() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BaseCell();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 衝突したら
	/// </summary>
	/// <param name="isHit">衝突判定</param>
	virtual void OnCollision(bool isHit);

	/// <summary>
	/// スケールのセッター
	/// </summary>
	/// <param name="scale">スケール</param>
	void SetScale(const Vector3 scale);

	/// <summary>
	/// 回転のセッター
	/// </summary>
	/// <param name="rotate">回転</param>
	void SetRotate(const Vector3 rotate);

	/// <summary>
	/// 平行移動のセッター
	/// </summary>
	/// <param name="translate">移動</param>
	void SetTranslate(const Vector3 translate);

	/// <summary>
	/// ワイヤーモデルのゲッター
	/// </summary>
	/// <returns></returns>
	Hexagon* GetWireModel();

	/// <summary>
	/// ワイヤーモデルのセッター
	/// </summary>
	/// <param name="hexagon">六角形</param>
	void SetWireModel(Hexagon*hexagon);

	/// <summary>
	/// 親子付け
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent);

protected: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	Hexagon* hexagon_ = nullptr;
	bool isHit_ = false;
};
