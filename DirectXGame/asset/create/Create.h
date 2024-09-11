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
		kPlayerHead,
		kPlayerBody,
		kPlayerLeft_Arm,
		kPlayerRight_Arm,
		kPlayerLeft_Ear,
		kPlayerRight_Ear,
		kEnemy,
		kSkyDome,
		kDeathParticles,
		kWarp,
		kModelNum,
    };
    using ObjectType=Type;//エイリアス
	ObjectType typePlayerHead = Type::kPlayerHead;//プレイヤー
	ObjectType typePlayerBody = Type::kPlayerBody;
	ObjectType typePlayerLeft_Arm = Type::kPlayerLeft_Arm;
	ObjectType typePlayerRight_Arm = Type::kPlayerRight_Arm;
	ObjectType typePlayerLeft_Ear = Type::kPlayerLeft_Ear;
	ObjectType typePlayerRight_Ear = Type::kPlayerRight_Ear;
	ObjectType typeEnemy = Type::kEnemy;//障害物
	ObjectType typeSkyDome = Type::kSkyDome;//天球
	ObjectType typeWarp = Type::kWarp;//ワープポインタ
	ObjectType typeDeathParticles = Type::kDeathParticles;
    static constexpr int MODEL_NUM = static_cast<int>(Type::kModelNum);//モデルの数

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

private: // メンバ変数
	std::vector<Model*> models_;//モデル
	std::vector<uint32_t> textureHandle_;//テクスチャ
};
