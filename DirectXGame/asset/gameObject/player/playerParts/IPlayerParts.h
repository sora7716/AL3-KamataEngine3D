#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// プレイヤーのパーツのインターフェース
/// </summary>
class IPlayerParts {

public://列挙型

	//パーツの名前
	enum class Parts {
		kHead,      // 頭
		kBody,      // 体
		kArm,       // 腕
		kLeft_Arm,  // 左腕
		kRight_Arm, // 右腕
		kPartsNum   // パーツ数
	};

public://メンバ関数

	using PartsName = Parts;
	static inline PartsName head = Parts::kHead;
	static inline PartsName body = Parts::kBody;
	static inline PartsName arm = Parts::kArm;
	static inline PartsName left_Arm = Parts::kLeft_Arm;
	static inline PartsName right_Arm = Parts::kRight_Arm;

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

protected: // メンバ変数

	///モデル
	Model* model_ = nullptr;

	///ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	///ワールドトランスドーム
	WorldTransform worldTransform_;

	//パーツノ位置
	Vector3 position_ = {};
	//パーツの角度
	Vector3 angle_ = {};
};