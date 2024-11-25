#pragma once
#include <cmath>
#define USE_MATH_DEFINES
#include "Model.h"
#include "TextureManager.h"
#include <memory>
#include <vector>

// 前方宣言
class Model;

/// <summary>
/// クリエイトクラス
/// </summary>
class Create final {
public: // 構造体や列挙型
	// 環境のオブジェクト
	enum class Type {
		kHexagon,
		kSkyDome,
		kGround,
		kModelNum,
	};

	// プレイヤーのモデル
	enum class PlayerType {
		kBody,
		kHead,
		kRightArm,
		kLeftArm,
		kPlayerNum,
	};
	// 環境のオブジェクト
	using ObjectType = Type; // エイリアス
	ObjectType typeHexagon = Type::kHexagon;
	ObjectType typeSkydome = Type::kSkyDome;
	ObjectType typeGround = Type::kGround;
	static inline const int MODEL_NUM = static_cast<int>(Type::kModelNum); // モデルの数
	// プレイヤーのモデル
	int typeHead = (int)PlayerType::kHead;         // 頭
	int typeBody = (int)PlayerType::kBody;    // 体
	int typeRightArm = (int)PlayerType::kRightArm; // 右腕
	int typeLeftArm = (int)PlayerType::kLeftArm;   // 左腕
	static inline const int PLAYER_MODEL_NUM = static_cast<int>(PlayerType::kPlayerNum);

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
	/// プレイヤーのモデルのゲッター
	/// </summary>
	/// <returns>モデル</returns>
	std::vector<std::unique_ptr<Model>>& GetPlayerModel();

	/// <summary>
	/// テクスチャのゲッター
	/// </summary>
	/// <param name="subscript">添え字</param>
	/// <returns>テクスチャハンドル</returns>
	uint32_t GetTextureHandle(Create::Type subscript) const;

	// コピーコンストラクタを禁止
	Create(const Create& create) = delete;

	// 代入演算を禁止
	Create& operator=(const Create& create) = delete;

private: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Create();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Create();

private:                                               // メンバ変数
	std::vector<std::unique_ptr<Model>> models_;       // モデル
	std::vector<std::unique_ptr<Model>> playerModels_; // プレイヤーのモデル
	std::vector<uint32_t> textureHandle_;              // テクスチャ
};
