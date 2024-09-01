#pragma once
#include <cmath>
#define USE_MATH_DEFINES
// 前方宣言
class Model;

/// <summary>
/// クリエイトクラス
/// </summary>
class Create {
public: // 構造体や列挙型
	enum class Type {
		kPlayer,
		kPlayerBullet,
		kEnemy,
		kEnemyBullet,
		kSkydome,
		kGround,
		kModelNum,
	};
    using ObjectType=Type;//エイリアス
	ObjectType typePlayer = Type::kPlayer;
	ObjectType typePlayerBullet = Type::kPlayerBullet;
	ObjectType typeEnemy = Type::kEnemy;
	ObjectType typeEnemyBullet = Type::kEnemyBullet;
	ObjectType typeSkydome = Type::kSkydome;
	ObjectType typeGround = Type::kGround;
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
	Model* models_[MODEL_NUM] = {nullptr};
	uint32_t textureHandle_[MODEL_NUM] = {0u};
};
