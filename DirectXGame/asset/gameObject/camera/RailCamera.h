#pragma once
#include "WorldTransform.h"

//�O���錾
class ViewProjection;

/// <summary>
/// ���[���J����
/// </summary> 
class RailCamera {

public: // �����o�֐�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RailCamera() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RailCamera() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

private: // �����o�ϐ�

	WorldTransform worldTransform_;  // ���[���h�ϊ��f�[�^

	ViewProjection* viewProjection_; // �r���[�v���W�F�N�V����

};
