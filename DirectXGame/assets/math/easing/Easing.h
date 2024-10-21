#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

/// <summary>
/// イージング
/// </summary>
class Easing {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Easing() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Easing() = default;

	/// <summary>
	/// インサイン
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InSine(float frame);

	/// <summary>
	/// アウトサイン
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float OutSine(float frame);

	/// <summary>
	/// インアウトサイン
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOutSine(float frame);

	/// <summary>
	/// インバック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InBack(float frame);

	/// <summary>
	/// アウトバック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float OutBack(float frame);

	/// <summary>
	/// アウトエラスティック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float OutElastic(float frame);

	/// <summary>
	/// インエクスポ
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InExpo(float frame);

	/// <summary>
	/// インアウトエクスポ
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOutExpo(float frame);

	/// <summary>
	/// インアウトバック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOutBack(float frame);

	/// <summary>
	/// アウトバウンス
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float OutBounce(float frame);

	/// <summary>
	/// インアウトバウンス
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOutBounce(float frame);

	/// <summary>
	/// インアウトクォート
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOutQuart(float frame);

	/// <summary>
	/// インアウトシーク
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOutCirc(float frame);

	/// <summary>
	/// インアウトクビック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOutCubic(float frame);

	/// <summary>
	/// インエラスティック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InElastic(float frame);

	/// <summary>
	/// インバウンス
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InBounce(float frame);

	/// <summary>
	/// アウトシーク
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float OutCirc(float frame);

	/// <summary>
	/// アウトクワァッド
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float OutQuad(float frame);
};
