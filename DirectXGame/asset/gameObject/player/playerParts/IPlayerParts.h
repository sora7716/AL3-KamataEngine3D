#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "cassert"
#include "numbers"

class IPlayerParts {

public://メンバ関数

	enum class Parts {
		kHead,      // 頭
		kBody,      // 体
		kLeft_Arm,  // 左腕
		kRight_Arm, // 右腕
		kPartsNum    // パーツ数
	};

	using PartsName = Parts;
	static inline PartsName head = Parts::kHead;
	static inline PartsName body = Parts::kBody;
	static inline PartsName Left_Arm = Parts::kLeft_Arm;
	static inline PartsName Right_Arm = Parts::kRight_Arm;

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

protected: //メンバ変数

	///モデル
	Model* model_ = nullptr;

	///ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	///ワールドトランスドーム
	WorldTransform worldTransform_;

};