#pragma once
#include "ViewProjection.h"
#include "Sprite.h"
#include <memory>
#include "assets/math/Math.h"

//前方宣言
class WorldTransfrom;

/// <summary>
/// プレイヤーの体力を表示する
/// </summary>
class LifeBar {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LifeBar(int characterType);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LifeBar() {}

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<uint32_t>&& textures);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 体力を描画する
	/// </summary>
	void Draw();
	/// <summary>
	/// ダメージを喰らったら更新処理
	/// </summary>
	void AdjustHP();
	/// <summary>
	/// isCollisionはtrueとなったら、Update()に入ってdamageを受けったとする
	/// </summary>
	void TookDamage();
	/// <summary>
	/// ダメージを受けたらcoolDownで永遠に受けないようにする
	/// </summary>
	void CoolDown();

	void DebugWindow();
private:
	enum class Label {
		kDamage,
		kHealth,
		kBorder,
		kNumOfLabels
	};

	std::vector<std::unique_ptr<Sprite>> sprites_;
	std::vector<uint32_t> textureHandle_;

	const static int width_ = 480;
	const static int height_ = 64;

	bool isDamaged_ = false;

	float currentHP_;
	float targetHP_;
	float maxHP_;
	float dmgTimer_;
	static inline const float kDuration_ = deltaTime * 1/2;

	Vector2 pos_;
	float coolDownTimer_ = 120;
	static inline const float coolDownDuration = deltaTime * 1 / 2;
};

