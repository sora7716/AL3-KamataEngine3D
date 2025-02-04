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
	/// <summary>
	/// 環境
	/// </summary>
	enum class Env { kSkaydome, kGround, kEnvNum };

	/// <summary>
	/// プレイヤー
	/// </summary>
	enum class PlayerParts { kBody, kFace, kEyeBrows, kHair, kLeftArm, kRightArm, kLeftThigh, kLeftLeg, kRightThigh, kRightLeg, kUpperCloth, kLowerCloth, kPartsNum };

public: // メンバ関数
	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns>クリエイトのインスタンス</returns>
	static Create* GetInstance();

	/// <summary>
	/// タイトルシーンのモデル
	/// </summary>
	void TitleSceneModel();

	/// <summary>
	/// ゲームシーンのモデル
	/// </summary>
	void GameSceneModel();

	/// <summary>
	/// エンドシーンのモデル
	/// </summary>
	void EndSceneModel();

	/// <summary>
	/// テクスチャの生成
	/// </summary>
	void TextureCreate();

	/// <summary>
	/// 環境モデルのゲッター
	/// </summary>
	/// <returns>環境モデル</returns>
	std::vector<std::shared_ptr<Model>>& GetEnvModel();

	/// <summary>
	/// プレイヤーパーツのゲッター
	/// </summary>
	/// <returns>プレイヤーモデル</returns>
	std::vector<std::shared_ptr<Model>>& GetPlayerModel();

	/// <summary>
	/// テクスチャのゲッター
	/// </summary>
	/// <returns></returns>
	std::vector<uint32_t> GetTextureHandle();

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
	std::vector<std::shared_ptr<Model>> envModels_;    // 環境モデル
	std::vector<std::shared_ptr<Model>> playerModels_; // プレイヤーモデル
	std::vector<uint32_t> textureHandles_;             // テクスチャ
};
