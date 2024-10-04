#pragma once
#include <cmath>
#define USE_MATH_DEFINES
#include <vector>

// 前方宣言
class Model;

/// <summary>
/// クリエイトクラス
/// </summary>
class Create {
public: // 構造体や列挙型
	enum class Type {
		kPlayer,
		kPlayerBody,           /// 体
		kPlayerHead,           /// 頭
		kPlayerRight_UpperArm, /// 右上腕
		kPlayerRight_LowerArm, /// 右腕
		kPlayerRight_Thigh,    /// 右もも
		kPlayerRight_Leg,      /// 右足
		kPlayerLeft_UpperArm,  /// 左上腕
		kPlayerLeft_LowerArm,  /// 左腕
		kPlayerLeft_Thigh,     /// 左もも
		kPlayerLeft_Leg,       /// 左足
		kModelNum,
	};
	using ObjectType = Type;                                                   // エイリアス
	static inline ObjectType typeBody = Type::kPlayerBody;                     // 体
	static inline ObjectType typeHead = Type::kPlayerHead;                     // 頭
	
	/// <summary>
	/// 右側のパーツ
	/// </summary>
	static inline ObjectType typeRight_UpperArm = Type::kPlayerRight_UpperArm; // 右上腕
	static inline ObjectType typeRight_LowerArm = Type::kPlayerRight_LowerArm; // 右腕
	static inline ObjectType typeRight_Thigh = Type::kPlayerRight_Thigh;       // 右もも
	static inline ObjectType typeRight_Leg = Type::kPlayerRight_Leg;           // 右足

	/// <summary>
	/// 左側のパーツ
	/// </summary>
	static inline ObjectType typeLeft_UpperArm = Type::kPlayerLeft_UpperArm;   // 左上腕
	static inline ObjectType typeLeft_LowerArm = Type::kPlayerLeft_LowerArm;   // 左腕
	static inline ObjectType typeLeft_Thigh = Type::kPlayerLeft_Thigh;         // 左もも
	static inline ObjectType typeLeft_Leg = Type::kPlayerLeft_Leg;             // 左足
	static constexpr int MODEL_NUM = static_cast<int>(Type::kModelNum);        // モデルの数

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Create();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Create();

	/// <summary>
	/// モデルをクリエイト
	/// </summary>
	void ModelCreate();

	/// <summary>
	/// テクスチャの生成
	/// </summary>
	void TextureCreate();

	/// <summary>
	/// モデルのゲッター
	/// </summary>
	/// <param name="num">添え字</param>
	/// <returns>モデル</returns>
	Model* GetModel(Create::Type subscript) const;

	/// <summary>
	/// テクスチャのゲッター
	/// </summary>
	/// <param name="subscript">添え字</param>
	/// <returns>テクスチャハンドル</returns>
	uint32_t GetTextureHandle(Create::Type subscript) const;

private:                                  // メンバ変数
	std::vector<Model*> models_;          // モデル
	std::vector<uint32_t> textureHandle_; // テクスチャ
};
