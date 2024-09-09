#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

/// <summary>
/// イージング
/// </summary>
class Easing{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Easing() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Easing() = default;

	/// <summary>
	/// �C��
	/// </summary>
	/// <param name="frame">�t���[��</param>
	/// <returns>�C�[�W���O</returns>
	static float In(float frame);

	/// <summary>
	/// �A�E�g
	/// </summary>
	/// <param name="frame">�t���[��</param>
	/// <returns>�C�[�W���O</returns>
	static float Out(float frame);

	/// <summary>
	/// �C���A�E�g
	/// </summary>
	/// <param name="frame">�t���[��</param>
	/// <returns>�C�[�W���O</returns>
	static float InOut(float frame);

	/// <summary>
	/// �C���o�b�N
	/// </summary>
	/// <param name="frame">�t���[��</param>
	/// <returns>�C�[�W���O</returns>
	static float InBack(float frame);

	/// <summary>
	/// アウトバック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns>イージング</returns>
	static float OutBack(float frame);

	/// <summary>
	/// イーズアウトエラスティック
	/// </summary>
	/// <param name="frame">フレーム</param>
	/// <returns></returns>
	static float EaseOutElastic(float frame);
};

