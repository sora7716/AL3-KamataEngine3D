#pragma once
#include "assets/gameManager/scene/game/baseGameObject/baseCharacter/BaseCharacter.h"
class BasePlayer : public BaseCharacter {
public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BasePlayer() = default;

	//純粋仮想関数
	virtual ~BasePlayer() = default;
	virtual void KeyboardControl() = 0;
	virtual void GamepadControl() = 0;
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models">モデルデータ</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

public: // メンバ変数
};
