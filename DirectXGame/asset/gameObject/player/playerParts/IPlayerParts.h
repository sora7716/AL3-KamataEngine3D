#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// プレイヤーのパーツのインターフェース
/// </summary>
class IPlayerParts {

public: // 列挙型
	// パーツの名前
	enum class Parts {
		kHead,      // 頭
		kBody,      // 体
		kArm,       // 腕
		kLeft_Arm,  // 左腕
		kRight_Arm, // 右腕
		kEar,       // 耳
		kLeftEar,   // 左耳
		kRightEar,  // 右耳
		kPartsNum   // パーツ数
	};

public: // メンバ関数
	using PartsName = Parts;
	static inline PartsName head = Parts::kHead;
	static inline PartsName body = Parts::kBody;
	static inline PartsName arm = Parts::kArm;
	static inline PartsName left_Arm = Parts::kLeft_Arm;
	static inline PartsName right_Arm = Parts::kRight_Arm;
	static inline PartsName ear = Parts::kEar;
	static inline PartsName left_Ear = Parts::kLeftEar;
	static inline PartsName right_Ear = Parts::kRightEar;

	static inline const int PartsNum = static_cast<int>(Parts::kPartsNum);

#pragma region 仮想純粋関数の宣言

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IPlayerParts() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="viewProjection"></param>
	virtual void Initialize(Model* model, ViewProjection* viewProjection) = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

#pragma endregion

	/// <summary>
	/// 親子関係を作る
	/// </summary>
	/// <param name="parent">ペアレント</param>
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform() { return worldTransform_; };

	/// <summary>
	/// ポジションのセッター
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const Vector3& position) { position_ = position; };

	/// <summary>
	/// 角度のセッター
	/// </summary>
	/// <param name="angle">角度</param>
	void SetAngle(const Vector3& angle) { angle_ = angle; };

	/// <summary>
	/// 拡縮、回転、平行移動のセッター
	/// </summary>
	void SetSRT() {
		worldTransform_.scale_ = size_;           // 拡縮
		worldTransform_.rotation_ = angle_;       // 回転
		worldTransform_.translation_ = position_; // 平行移動
	};

	/// <summary>
	/// ポジションのゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const { return position_; };

	/// <summary>
	/// 角度
	/// </summary>
	/// <returns></returns>
	Vector3 GetAngle() const { return angle_; };

protected: // メンバ変数
	/// モデル
	Model* model_ = nullptr;

	/// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	/// ワールドトランスドーム
	WorldTransform worldTransform_;

	// パーツノ位置
	Vector3 position_ = {};
	// パーツの角度
	Vector3 angle_ = {};
	// パーツのサイズ
	Vector3 size_ = {1.0f, 1.0f, 1.0f};
};