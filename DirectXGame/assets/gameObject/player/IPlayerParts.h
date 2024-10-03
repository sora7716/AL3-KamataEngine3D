#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "cassert"

#ifdef _DEBUG
#include "imgui.h"
using namespace ImGui;
#endif // _DEBUG

/// <summary>
/// プレイヤーパーツクラス
/// </summary>
class IPlayerParts {

public: /// 列挙体の宣言
	enum class Parts {
		kBody,          /// 体
		kHead,          /// 頭
		kLeft_UpperArm, /// 左上腕
		kLeft_LowerArm, /// 左腕
		kLeft_Thigh,    /// 左もも
		kLeft_Leg,      /// 左足
		kPartsNum       /// パーツ数
	};

	using PartsName = Parts;
	static inline PartsName body = Parts::kBody;                         /// 体
	static inline PartsName head = Parts::kHead;                         /// 頭
	static inline PartsName left_UpperArm = Parts::kLeft_UpperArm;       /// 左上腕
	static inline PartsName left_LowerArm = Parts::kLeft_LowerArm;       /// 左腕
	static inline PartsName left_Thigh = Parts::kLeft_Thigh;             /// 左もも
	static inline PartsName left_Leg = Parts::kLeft_Leg;                 /// 左足
	static constexpr int PARTS_NUM = static_cast<int>(Parts::kPartsNum); /// パーツ数

public:    /// メンバ関数の宣言

	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	IPlayerParts() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IPlayerParts() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Initialize(Model *model,ViewProjection *viewProjection) = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ワールドトランスフォームのgetter
	/// </summary>
	/// <returns>戻り値</returns>
	const WorldTransform& GetWorldTransform() { return this->worldTransform_; }

	/// <summary>
	/// 親子関係を結ぶ
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

	/// <summary>
	/// SRTアフィン
	/// </summary>
	void SetAffine() { 
		worldTransform_.scale_ = size_;
		worldTransform_.rotation_ = angle_;
		worldTransform_.translation_ = position_;
	}

protected: /// メンバ変数の宣言

	/// モデル
	Model* model_ = nullptr;

	/// ワールドトランスフォーム
	WorldTransform worldTransform_; 

	/// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	/// 倍率
	Vector3 size_ = {1, 1, 1};

	/// 角度
	Vector3 angle_ = {};

	/// 座標
	Vector3 position_ = {};

};