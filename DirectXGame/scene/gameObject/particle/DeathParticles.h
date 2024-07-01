#pragma once
#include "Vector4.h"
#include "WorldTransform.h"
#include <ObjectColor.h>
#include <array>
#include <cmath>
#include <numbers>
#define pi_f std::numbers::pi_v<float>
// 前方宣言
class Player;
class Model;
class ViewProjection;

class DeathParticles {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DeathParticles();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DeathParticles();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, Vector3 position, uint32_t textureHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private: // メンバ関数
	/// <summary>
	/// パーティクルが消えるまでの時間を計測
	/// </summary>
	void DestoryCount();

	/// <summary>
	/// 移動ベクトルの設定
	/// </summary>
	void SettingSpeed();

	/// <summary>
	/// フェードアウト
	/// </summary>
	void FadeOut();

public:                                                                                      // メンバ変数
	static inline const uint32_t kNumParticle = 8;                                           // パーティクルの数
	static inline const float kDuration = 2.0f;                                              // 存続時間(消滅までの時間)<秒>
	static inline const float kSpeed = 0.1f;                                                 // 移動スピード
	static inline const float kAngleUnit = (2.0f * pi_f) / static_cast<float>(kNumParticle); // 分割した1個分の角度

private:                                                       // メンバ変数
	std::array<WorldTransform, kNumParticle> worldTransforms_; // ワールドトランスフォーム
	ViewProjection* viewProjection_;                           // ビュープロジェクション
	Model* model_;                                             // モデル
	Player* player_;                                           // プレイヤー
	uint32_t textureHandle_;                                   // テクスチャ
	bool isFinished_;                                          // 終了フラグ
	float counter_;                                            // 経過時間カウント
	ObjectColor objectColor_;                                  // 色変更オブジェクト
	Vector4 color_;                                            // 色の数値
};
