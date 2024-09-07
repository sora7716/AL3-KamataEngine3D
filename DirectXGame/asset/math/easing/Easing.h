#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

/// <summary>
/// イージング
/// </summary>
class Easing{
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
	/// イン
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float In(float frame);

	/// <summary>
	/// アウト
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float Out(float frame);

	/// <summary>
	/// インアウト
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float InOut(float frame);

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
};

