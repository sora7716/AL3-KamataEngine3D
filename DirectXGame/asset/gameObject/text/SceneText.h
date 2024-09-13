#pragma once
#include "WorldTransform.h"

//前方宣言
class Model;
class ViewProjection;

/// <summary>
/// スペースを押せのクラス
/// </summary>
class SceneText {

public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection *viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	/// <summary>
	/// 位置のセッター
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const Vector3& position);

	/// <summary>
	/// 親子付け
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; };

private://メンバ関数

	void ResultEaseInMove();
	void ResultEaseOutMove();


private:

	Model* model_ = nullptr;//モデル

	ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション

	WorldTransform worldTransform_;//ワールドトランスフォーム

	//リザルトシーン用のフレーム
	float resultFrame[2] = {0, 0};

};
