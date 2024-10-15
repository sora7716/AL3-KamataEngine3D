#pragma once
#include <cmath>
#define USE_MATH_DEFINES
#include <vector>

// 前方宣言
class Model;

/// <summary>
/// クリエイトクラス
/// </summary>
class Create final{
public: // 構造体や列挙型
	enum class Type {
		kHexagon,
		kModelNum,
	};
	using ObjectType = Type;                       // エイリアス
	ObjectType typeHexagon = Type::kHexagon;
	static constexpr int MODEL_NUM = static_cast<int>(Type::kModelNum); // モデルの数

public: // メンバ関数

	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns>クリエイトのインスタンス</returns>
	static Create* GetInstance();

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

private://メンバ関数

	// コピーコンストラクタを禁止
	Create(const Create& create) = delete;

	// 代入演算を禁止
	Create& operator=(const Create& create) = delete;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Create();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Create();

private:// メンバ変数
	std::vector<Model*> models_;          // モデル
	std::vector<uint32_t> textureHandle_; // テクスチャ
};
