#pragma once
#include <memory>
#include <vector>
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	const WorldTransform& GetWorldTransform();

	/// <summary>
	/// matでの行列情報を取り出す
	/// </summary>
	/// <returns></returns>
	const Vector3 GetWorldPos();
	
protected://メンバ変数
	//モデルデータ配列
	std::vector<Model*> models_;
	//ワールド変換データの配列
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection* viewProjection_;
	//
};
