#pragma once
#include "WorldTransform.h"
#include "asset/math/Aithmetic.h"
#include "asset/math/collision/Collision.h"
#include "asset/gameObject/player/playerParts/PlayerParts.h"
#include "asset/gameObject/player/patricle/DeathParticles.h"

//前方宣言(苦肉の策)
class ViewProjection;
class Create;
class Hp;
class SkyDome;

/// <summary>
/// プレイヤー
/// </summary>
class Player {
public: // 列挙型
	// プレイヤーの状態
	enum class Phase {
		kStart, // 始まり
		kPlay,  // ゲームプレイ
		kDeth,  // 死亡
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Create* create, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="firePos">耳を飛ばす場所</param>
	void Update(float firePos = 0.0f);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突したときの処理
	/// </summary>
	void OnCollision(int hpCount);

#pragma region コマンド
	/// <summary>
	/// 右方向移動
	/// </summary>
	void MoveRight();

	/// <summary>
	/// 左方向移動
	/// </summary>
	void MoveLeft();

	/// <summary>
	/// 上方向移動
	/// </summary>
	void MoveUp();

	/// <summary>
	/// 下方向移動
	/// </summary>
	void MoveDown();
#pragma endregion

	/// <summary>
	/// プレイヤーの動ける上限
	/// </summary>
	void MoveLimit();

	/// <summary>
	/// 親子関係作る
	/// </summary>
	void SetPearent(const WorldTransform* parent);

	/// <summary>
	/// 位置のセッター
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const Vector3& position);

	/// <summary>
	/// 角度のセッター
	/// </summary>
	/// <param name="rotation">角度</param>
	void SetRotation(const Vector3& rotation);

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform();

	/// <summary>
	/// パーツの位置のセッター
	/// </summary>
	/// <param name="partsType">パーツの場所</param>
	/// <param name="position">位置</param>
	void SetPartsPosition(IPlayerParts::PartsName partsType, const Vector3& position);

	/// <summary>
	/// パーツの角度のセッター
	/// </summary>
	/// <param name="partsName">パーツの部位</param>
	/// <param name="angle">角度</param>
	void SetPartsAngle(IPlayerParts::PartsName partsName, const Vector3& angle);

	/// <summary>
	/// アニメーションを行うかどうかのフラグのセッター
	/// </summary>
	/// <param name="partsName">パーツの部位</param>
	/// <param name="isAnimation">アニメーションを行うかどうか</param>
	void SetPartsIsAnimation(IPlayerParts::PartsName partsName, bool isAnimation);

	/// <summary>
	/// パーツの位置のゲッター
	/// </summary>
	/// <param name="partsName">パーツの部位</param>
	/// <returns>position</returns>
	Vector3 GetPartsPosition(IPlayerParts::PartsName partsName) const;

	/// <summary>
	/// パーツの角度のゲッター
	/// </summary>
	/// <param name="partsName">パーツの部位</param>
	/// <returns></returns>
	Vector3 GetPartsAngle(IPlayerParts::PartsName partsName) const;

	/// <summary>
	/// プレイヤーの消滅
	/// </summary>
	void PlayerDead();

	/// <summary>
	/// 無敵時間がスタートするかどうかのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsStartFrash();

	/// <summary>
	/// 透明なのかのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsInvisible_();

	/// <summary>
	/// 耳飛ばしたのが1回目かどうかのフラグのセッター
	/// </summary>
	/// <param name="isShotFirstTime">設定したいフラグ</param>
	void SetIsShotFirstTime(bool isShotFirstTime);

	/// <summary>
	/// ワープポイントがスポーンしているかどうかのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsWarpSpawn();

	/// <summary>
	/// スカイドームのセッター
	/// </summary>
	/// <param name="skyDome">スカイドーム</param>
	void SetSkyDome(SkyDome* skyDome);
	void SceneTransition();

	int IsStartFrash();

	/// <summary>
	/// プレイヤーのスケール
	/// </summary>
	void SetScale(const Vector3& scale);

	bool IsDead() { return this->isDead_; }

	bool IsParticleShot() { return this->isParticleShot_; }

	bool IsSceneTransition() { return this->isSceneTransition; }

private: // メンバ関数
	/// <summary>
	/// パーツを作る
	/// </summary>
	void CreateParts();

	/// <summary>
	/// パーツの初期化
	/// </summary>
	void InitializeParts();

#pragma region 右腕を飛ばす

	// 角度も動かす
	void Right_Arm_MoveAngle();

	// 衝突時、座標を動かす
	void Right_Arm_MovePosition();

	void Right_Arm_Fly();

#pragma endregion

#pragma region 左腕を飛ばす

	// 衝突時、座標を動かす
	void Left_Arm_MovePosition();
	// 角度も動かす
	void Left_Arm_MoveAngle();

	void Left_Arm_Fly();

#pragma endregion

	// 無敵時間
	void Unrivaled();

	/// <summary>
	/// パーティクルの初期化
	/// </summary>
	void InitializeParticles();

#pragma region 頭を飛ばす

	void Head_MoveAngle();//角度

	void Ear_MovePosition();//耳の座標

	void Head_MovePosition();//座標

	void Head_Fly();

#pragma endregion 
	
#pragma region 体を飛ばす

	void Body_MoveAngle();//角度

	void Body_MovePosition();//座標

	void Body_Fly();

#pragma endregion
	

	/// <summary>
	/// 耳を飛ばす
	/// </summary>
	/// <param name="firePos">耳を飛ばす位置</param>
	void EarShot(float firePos);

public://静的メンバ変数

	///キャラクターの移動速度
	static inline const float kCharacterSpeed = 0.2f;
	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 3.0f;  // 横幅
	static inline const float kHeight = 3.0f; // 立幅
	static inline const float kDepth = 2.0f;  // 深さ

private://メンバ変数

	///ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	///ワールドトランスフォーム
	WorldTransform worldTransform_;

	//速度
	Vector3 velocity_ = {};

	//プレイヤーの状態
	Phase phase_ = Phase::kStart;

	//パーツ
	std::unique_ptr<IPlayerParts> parts_[IPlayerParts::PartsNum] = {nullptr};
	std::unique_ptr<IDeathParticle> particles_[IDeathParticle::particleNum] = {nullptr};

	// クリエイトクラス
	Create* create_ = nullptr; 

	bool isDead_ = false;//死んだとき
	int hpCount_ = 3;//HPのカウント

	//無敵時間
	static void (Player::*parts_flyTable[])();//メンバ関数ポインタテーブル
	bool isFrashStart_ = false;//無敵時間をスタートさせるかどうか
	bool isInvisible_ = false;//透明かどうか
	int coolTimer = 0;//無敵時間のクールタイム

	//耳を飛ばすときの変数
	Vector3 leftEarPosition_ = {};//耳の位置
	float leftEarSize_ = 1.0f;//耳の大きさ
	bool isEarShot_ = false;//耳を飛ばすときのフラグ
	bool isShotFirstTime_ = false;//耳飛ばしたのが1回目かどうかのフラグ

	bool isWarpSpawn_ = false;//ワープポイントのスポーンするかどうかのフラグ
	SkyDome* skyDome_ = nullptr;//スカイドーム
	int coolTimer = 0;
	
	int parts_FlyTimer = 0;
	bool isParticleShot_ = false; // パーティクルが発射されてるか
	bool isSceneTransition = false; //シーンを遷移するか

};
