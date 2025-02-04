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
	/// モデルのゲッター
	/// </summary>
	/// <returns>モデル</returns>
	std::vector<std::shared_ptr<Model>>& GetEnvModel();

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

private:// メンバ変数
	std::vector<std::shared_ptr<Model>> envModels_; // モデル
	std::vector<uint32_t> textureHandles_;          // テクスチャ
};
