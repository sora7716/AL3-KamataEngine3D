#pragma once
#include "WorldTransform.h"
#include "asset/gameObject/player/bullet/PlayerBullet.h"
#include <list>
using namespace std;

// 前方宣言
class Model;
class ViewProjection;
class Input;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="texture">テクスチャ</param>
	void Initialize(Model* model, ViewProjection* viewProjection, uint32_t texture);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 速度のセッター
	/// </summary>
	/// <param name="velocity">速度</param>
	void SetVelocity(Vector3 velocity);


#pragma region コマンド
	/// <summary>
	/// 左へ移動
	/// </summary>
	void MoveLeft();

	/// <summary>
	/// 右へ移動
	/// </summary>
	void MoveRight();

	/// <summary>
	/// 下へ移動
	/// </summary>
	void MoveDown();

	/// <summary>
	/// 上へ移動
	/// </summary>
	void MoveUp();

	/// <summary>
	/// 右回り
	/// </summary>
	void RotateRight();

	/// <summary>
	/// 左回り
	/// </summary>
	void RotateLeft();
#pragma endregion

private: // メンバ関数
#ifdef _DEBUG
	void DebugText();
#endif // _DEBUG

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

public:// 静的メンバ変数

	static inline const float kCharacterSpeed = 0.2f; // キャラクターの移動量
	static inline const float kRotSpeed = 0.02f;      // 回転の速さ[ラジアン/frame]

private:// メンバ変数
	
	Model* model_ = nullptr;                           // モデル
	ViewProjection* viewProjection_ = nullptr;         // ビュープロジェクション
	WorldTransform worldTransform_;                    // ワールドトランスフォーム
	uint32_t texture_ = 0u;                            // テクスチャ
	Input* input_ = nullptr;                           // キー入力
	Vector3 velocity_ = {};                            // キャラクターの移動速度
	list<PlayerBullet*> bullets_ = {nullptr};          // 弾
};
