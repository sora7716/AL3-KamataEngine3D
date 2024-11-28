#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
/// <summary>
/// イージング
/// </summary>
class Easing final {
public: // 列挙型
	// イージングのモード
	enum class Mode {
		// サイン
		kInSine,
		kOutSine,
		kInOutSine,
		// バック
		kInBack,
		kOutBack,
		kInOutBack,
		// バウンス
		kInBounce,
		kOutBounce,
		kInOutBounce,
		// エクスポ
		kInExpo,
		kInOutExpo,
		// シーク
		kOutCirc,
		kInOutCirc,
		// クワァッド
		kInQuad,
		kOutQuad,
		// エラスティック
		kInElastic,
		kOutElastic,
		// クワァード
		kInOutQuart,
		// クビット
		kInOutCubic,
	};

public: // メンバ関数

	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static Easing* GetInstance();

	// コピーコンストラクタを禁止
	Easing(const Easing& easing) = delete;

	// 代入演算子を禁止
	Easing& operator=(const Easing& easing) = delete;

private: // メンバ関数

	/// <summary>
	/// インサイン
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InSine(float frame);

	/// <summary>
	/// アウトサイン
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float OutSine(float frame);

	/// <summary>
	/// インアウトサイン
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InOutSine(float frame);

	/// <summary>
	/// インバック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InBack(float frame);

	/// <summary>
	/// アウトバック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float OutBack(float frame);

	/// <summary>
	/// アウトエラスティック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float OutElastic(float frame);

	/// <summary>
	/// インエクスポ
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InExpo(float frame);

	/// <summary>
	/// インアウトエクスポ
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InOutExpo(float frame);

	/// <summary>
	/// インアウトバック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InOutBack(float frame);

	/// <summary>
	/// アウトバウンス
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float OutBounce(float frame);

	/// <summary>
	/// インアウトバウンス
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InOutBounce(float frame);

	/// <summary>
	/// インアウトクォート
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InOutQuart(float frame);

	/// <summary>
	/// インアウトシーク
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InOutCirc(float frame);

	/// <summary>
	/// インアウトクビック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InOutCubic(float frame);

	/// <summary>
	/// インエラスティック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InElastic(float frame);

	/// <summary>
	/// インバウンス
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float InBounce(float frame);

	/// <summary>
	/// アウトシーク
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float OutCirc(float frame);

	/// <summary>
	/// アウトクワァッド
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	float OutQuad(float frame);

	/// <summary>
	/// インクワァッド
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns></returns>
	float InQuad(float frame);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Easing() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Easing() = default;

public: // メンバ変数
	// 関数ポインタの配列
	static float (Easing::*EasingTable[])(float frame);
};
using EasingMode = Easing::Mode;
