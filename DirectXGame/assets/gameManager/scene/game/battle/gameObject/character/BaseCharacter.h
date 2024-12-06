#pragma once
#include <memory>
#include <vector>
#include "Model.h"
#include "assets/math/Math.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "assets/math/collision/Collision.h"

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class BaseCharacter {
public://メンバ関数

	enum class CharType {
		kPlayer,
		kEnemy
	};

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
	/// 当たり判定のため、matWorld_のゲッター
	/// </summary>
	/// <returns></returns>
	const Vector3 GetWorldPos();

	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	ViewProjection& GetViewProjection();

	/// <summary>
	/// モデルの縦幅情報をAABB型でゲッター
	/// </summary>
	/// <returns></returns>
	AABB GetAABB();

protected://メンバ変数
	//モデルデータ配列
	std::vector<Model*> models_;
	//ワールド変換データの配列
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection* viewProjection_;
	//CharacterType
	CharType charType_;

	//当たり判定
	float kWidth_, kHeight_, kDepth_;
};