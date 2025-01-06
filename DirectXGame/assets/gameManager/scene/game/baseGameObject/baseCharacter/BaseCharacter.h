#pragma once
#include <memory>
#include <vector>
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "assets/math/collision/shape/obb/OBB.h"

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class BaseCharacter {
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseCharacter() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseCharacter() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models">モデルデータ</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// ワイヤーフレームの表示
	/// </summary>
	void DrawWire();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label">ラベル</param>
	virtual void DebugText(const char* label);

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	const WorldTransform& GetWorldTransform();

	/// <summary>
	/// matでの行列情報を取り出す
	/// </summary>
	/// <returns></returns>
	const Vector3 GetWorldPos();
	
	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	ViewProjection& GetViewProjection();

protected://メンバ変数
	//モデルデータ配列
	std::vector<Model*> models_;
	//ワールド変換データの配列
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection* viewProjection_;
	OBB* wireFrame_ = nullptr;
	Vector3 colliderPos_ = {};
	Vector3 colliderScale_ = {1.0f,1.0f,1.0f};
};
