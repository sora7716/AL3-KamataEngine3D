#pragma once
#include "Sprite.h"
/// <summary>
/// フェード
/// </summary>
class Fade {

public: // 構造体など
	// フェードの状態
	enum class Status {
		None,    // フェードなし
		FadeIn,  // フェードイン中
		FadeOut, // フェードアウト中
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクター
	/// </summary>
	Fade();

	/// <summary>
	/// デストラクター
	/// </summary>
	~Fade();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// フェード開始
	/// </summary>
	/// <param name="status">フェードの状態</param>
	/// <param name="duration">フェードの継続時間</param>
	void FadeStart(Status status, float duration);

	/// <summary>
	/// フェードの停止
	/// </summary>
	void FadeStop();

	/// <summary>
	/// フェードの終了判定
	/// </summary>
	/// <returns></returns>
	bool IsFinished() const;

private: // メンバ関数

	/// <summary>
	/// フェードアウトの処理
	/// </summary>
	void FadeOut();

	/// <summary>
	/// フェードインの処理
	/// </summary>
	void FadeIn();

private:                           // メンバ変数
	Sprite* sprite_ = nullptr;     // スプライト
	uint32_t textureHandle_ = 0u;  // テクスチャ
	Status status_ = Status::None; // 現在のフェードの状態
	float duration_ = 0.0f;        // フェードの継続時間
	float counter_ = 0.0f;         // 経過時間カウンター
};
