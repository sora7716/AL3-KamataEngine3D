#pragma once
#include "asset/math/collision/Collision.h"
#include "WorldTransform.h"
#include <list>
using namespace std;

// 前方宣言(苦肉の策)
class Model;
class ViewProjection;
class Input;
class GameScene;

/// <summary>
/// プレイヤー
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
	/// <param name="position">ポジション</param>
	void Initialize(Model* model, ViewProjection* viewProjection, uint32_t texture, Vector3 position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 速度のセッター
	/// </summary>
	/// <param name="velocity">速度</param>
	void SetVelocity(Vector3 velocity);

	/// <summary>
	/// ワールドポジションのゲッター
	/// </summary>
	/// <returns>ワールド座標</returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// ペアレントのトランスレイションのゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetParentTranslation();

	/// <summary>
	/// ペアレントのローテションのゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetParentRotation();

	/// <summary>
	/// ゲームシーンのセッター
	/// </summary>
	/// <param name="gameScene">ゲームシーン</param>
	void SetGameScene(GameScene*gameScene);

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

public: // 静的メンバ変数

	static inline const float kCharacterSpeed = 0.2f; // キャラクターの移動量
	static inline const float kRotSpeed = 0.02f;      // 回転の速さ[ラジアン/frame]
	static inline const float kBulletSpeed = 1.0f;    // 弾の速度
	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 1.0f;  // 横幅
	static inline const float kHeight = 1.0f; // 立幅
	static inline const float kDepth = 1.0f;  // 深さ

private: // メンバ変数
	Model* model_ = nullptr;                   // モデル
	ViewProjection* viewProjection_ = nullptr; // ビュープロジェクション
	WorldTransform worldTransform_;            // ワールドトランスフォーム
	uint32_t texture_ = 0u;                    // テクスチャ
	Input* input_ = nullptr;                   // キー入力
	Vector3 velocity_ = {};                    // キャラクターの移動速度
	Vector3 parentRotation_ = {};
	Vector3 parentTranslation_{};
	GameScene* gameScene_ = nullptr; // ゲームシーン
};
