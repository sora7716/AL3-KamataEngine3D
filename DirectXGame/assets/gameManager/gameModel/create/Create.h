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
		kParticle,
		kModelNum,
	};
	// 環境のオブジェクト
	int typeHexagon = (int)Type::kHexagon;
	int typeSkydome = (int)Type::kSkyDome;
	int typeGround = (int)Type::kGround;
	int typeParticle = (int)Type::kParticle;
	// プレイヤーのモデル
	enum class PlayerParts {
		kBody,
		kHead,
		kRightArm,
		kLeftArm,
		kStaff,
		kPlayerNum,
	};
	// プレイヤーのモデル
	int typeHead = (int)PlayerParts::kHead;         // 頭
	int typeBody = (int)PlayerParts::kBody;         // 体
	int typeRightArm = (int)PlayerParts::kRightArm; // 右腕
	int typeLeftArm = (int)PlayerParts::kLeftArm;   // 左腕
	int typeStaff = (int)PlayerParts::kStaff;
	// ミミックのモデル
	enum class MimicParts { kBox, kLid, kEye, kToothUp, kToothBottom, kTongue, kPartsNum };
	// プレイヤーのモデル
	int typeBox = (int)MimicParts::kBox;                 // 箱
	int typeLid = (int)MimicParts::kLid;                 // 蓋
	int typeEye = (int)MimicParts::kEye;                 // 目
	int typeToothUp = (int)MimicParts::kToothUp;         // 上の歯
	int typeToothBottom = (int)MimicParts::kToothBottom; // 下の歯
	int typeTongue = (int)MimicParts::kTongue;           // 舌
public:                                                  // メンバ関数
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
	Model* GetModel(int subscript) const;

	/// <summary>
	/// プレイヤーのモデルのゲッター
	/// </summary>
	/// <returns>モデル</returns>
	std::vector<std::unique_ptr<Model>>& GetPlayerModel();

	/// <summary>
	/// ミミックのモデルのゲッター
	/// </summary>
	/// <returns>モデル</returns>
	std::vector<std::unique_ptr<Model>>& GetMimicModel();

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
	std::vector<std::unique_ptr<Model>> mimicModels_;  // ミミックのモデル
	std::vector<uint32_t> textureHandle_;              // テクスチャ
};
