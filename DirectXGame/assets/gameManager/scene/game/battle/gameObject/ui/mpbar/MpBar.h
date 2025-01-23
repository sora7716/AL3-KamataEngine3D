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
class MpBar {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MpBar(int characterType);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MpBar() {}

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<uint32_t>&& textures);

	/// <summary>
	/// 更新
	/// </summary>
	bool Update();

	/// <summary>
	/// 体力を描画する
	/// </summary>
	void Draw();
	/// <summary>
	/// ダメージを喰らったら更新処理
	/// </summary>
	void AdjustMP();
	/// <summary>
	/// isCollisionはtrueとなったら、Update()に入ってdamageを受けったとする
	/// </summary>
	void UsedMP();
	/// <summary>
	/// ダメージを受けたらcoolDownで永遠に受けないようにする
	/// </summary>
	void CoolDown();

	void DebugWindow();

	bool GetIsEmpty() { return isEmpty_; }
private:
	enum class MpLabel {
		placeHolder0,
		placeHolder1,//placeHolderはHPバーの画像です
		placeHolder2,
		placeHolder3,
		kCost,
		kMp,
		kBorder,
		kNumOfLabels
	};

	std::vector<std::unique_ptr<Sprite>> sprites_;
	std::vector<uint32_t> textureHandle_;

	const static int width_ = 480;
	const static int height_ = 64;

	bool isCasted_ = false;
	bool isEmpty_ = false;

	float currentMp_ = 0;
	float targetMp_ = 0;
	float maxMp_ = 0;
	float costTimer_ = 0;
	int characterType_ = 0;
	static inline const float kDuration_ = deltaTime * 1 / 2;

	Vector2 pos_;
	float coolDownTimer_ = 120;
	static inline const float coolDownDuration = deltaTime * 1 / 2;
};