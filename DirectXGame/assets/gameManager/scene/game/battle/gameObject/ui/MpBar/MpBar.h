#pragma once
#include "ViewProjection.h"
#include "Sprite.h"
#include <memory>
#include "assets/math/Math.h"

//前方宣言
class WorldTransform;
;;  
class MpBar{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MpBar();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MpBar(){}

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="textures"></param>
	void Initialize(const std::vector<uint32_t>&& textures);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 攻撃によっての減少分を更新（LERP)
	/// </summary>
	void AdjustMP();

	/// <summary>
	/// 攻撃した時点、MPを減少し、coolDownTimerに入る
	/// </summary>
	void MpUsed();

	/// <summary>
	/// クールダウン処理
	/// </summary>
	void CoolDown();

	/// <summary>
	/// デバッグウインドウ
	/// </summary>
	void DebugWindow();

	float GetMp() { return currentMP_; }

private:
	enum class Label {
		kCost,
		kMagicPoints,
		kBorder,
		kNumOfLabels
	};

	std::vector<std::unique_ptr<Sprite>> sprites_;
	std::vector<uint32_t> textureHandle_;

	const static int width_ = 480; //借り値
	const static int height_ = 64; //借り値

	bool isAttack_ = false; //MPを使ったら

	float currentMP_; //現在値
	float targetMP_; //目標値
	float mapMP_; //最大値
	float mpTimer_; //タイマー

	static inline const float kDuration_ = deltaTime * 1 / 2;

	Vector2 pos_;
	float coolDownTimer_ = 120; //クールダウンタイマー
	static inline const float coolDownDuration = deltaTime * 1 / 2;
};

