#pragma once
#include "WorldTransform.h"

// 前方宣言
class Model;
class ViewProjection;
class TitleFont {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleFont() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleFont() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ゲームスタートを選択したかのフラグのセッター
	/// </summary>
	/// <param name="isSelectGameStart"></param>
	void SetIsSelectGameStart(bool isSelectGameStart);

	/// <summary>
	/// ゲームをスタートさせるかのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsGameStartAnimation() { return isGameStartAnimation_; };

private: // メンバ関数
	/// <summary>
	/// フォントの動き
	/// </summary>
	void MoveFont();

private: // メンバ変数
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// 現在のフレーム
	float frame_ = 0.0;
	//タイトルを設置する
	bool isPut = true;
	//元の位置に戻す
	bool isBack_ = false;
	//少し待つ
	float stayTime_ = 0.0f;
	//ゲームをスタートする
	bool isGameStartAnimation_ = false;
	//ゲームスタートを選択したかのフラグ
	bool isSelectGameStart_ = false;
};
