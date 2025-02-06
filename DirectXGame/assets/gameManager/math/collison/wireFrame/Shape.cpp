#include "Shape.h"

// ローカルの頂点を変換
Vector3 Shape::Conversion(const Vector3& scale, const Vector3& rotate, const Vector3& translate, const Vector3& kLocalVertex) {
	// ワールド行列を生成
	worldMatrix_ = Math::MakeAffineMatrix(scale, rotate, translate);
	// ローカルの頂点とくっつける
	return Math::Transform(kLocalVertex, worldMatrix_);
}

// ローカルの頂点を変換(scale無いver)
Vector3 Shape::Conversion(const Vector3& rotate, const Vector3& translate, const Vector3& kLocalVertex) {
	// ワールド行列を生成
	worldMatrix_ = Math::MakeAffineMatrix(rotate, translate);
	// ローカルの頂点とくっつける
	return Math::Transform(kLocalVertex, worldMatrix_);
}

// OBB用ローカルの頂点を変換
Vector3 Shape::Conversion(const Vector3& rotate, const Vector3& translate, const Vector3& kLocalVertex, Vector3* orientations, const Matrix4x4* parentoMatWorld) {
	MakeOBBRotateMatrix(orientations, rotate);                  // OBB用の回転行列を抽出
	worldMatrix_ = MakeOBBWorldMatrix(orientations, translate); // OBB用のワールド行列を作成
	if (parentoMatWorld) {
		worldMatrix_ = *parentoMatWorld * worldMatrix_;
	}
	// ローカルの頂点とくっつける
	return Math::Transform(kLocalVertex, worldMatrix_);
}

// OBB用ローカルの頂点を変換
Vector3 Shape::Conversion(const Vector3& rotate, const Vector3& kLocalVertex, Vector3* orientations) {
	MakeOBBRotateMatrix(orientations, rotate);       // OBB用の回転行列を抽出
	worldMatrix_ = MakeOBBWorldMatrix(orientations); // OBB用のワールド行列を作成
	// ローカルの頂点とくっつける
	return Math::Transform(kLocalVertex, worldMatrix_);
}

// OBB用の回転行列
void Shape::MakeOBBRotateMatrix(Vector3* orientations, const Vector3& rotate) {
	Matrix4x4 rotateMatrix = Math::MakeRotateXYZMatrix(rotate);

	// 回転行列からの抽出

	// X'
	orientations[0].x = rotateMatrix.m[0][0];
	orientations[0].y = rotateMatrix.m[0][1];
	orientations[0].z = rotateMatrix.m[0][2];

	// Y'
	orientations[1].x = rotateMatrix.m[1][0];
	orientations[1].y = rotateMatrix.m[1][1];
	orientations[1].z = rotateMatrix.m[1][2];

	// Z'
	orientations[2].x = rotateMatrix.m[2][0];
	orientations[2].y = rotateMatrix.m[2][1];
	orientations[2].z = rotateMatrix.m[2][2];
}

// OBB用のワールド行列
Matrix4x4 Shape::MakeOBBWorldMatrix(const Vector3* orientations, const Vector3 center) {
	Matrix4x4 result{
	    orientations[0].x, orientations[0].y, orientations[0].z, 0.0f, orientations[1].x, orientations[1].y, orientations[1].z, 0.0f,
	    orientations[2].x, orientations[2].y, orientations[2].z, 0.0f, center.x,          center.y,          center.z,          1.0f,
	};
	return result;
}

// OBB用のワールド行列
Matrix4x4 Shape::MakeOBBWorldMatrix(const Vector3* orientations) {
	Matrix4x4 result{
	    orientations[0].x,
	    orientations[0].y,
	    orientations[0].z,
	    0.0f,
	    orientations[1].x,
	    orientations[1].y,
	    orientations[1].z,
	    0.0f,
	    orientations[2].x,
	    orientations[2].y,
	    orientations[2].z,
	    0.0f,
	    0.0f,
	    0.0f,
	    0.0f,
	    1.0f,
	};
	return result;
}

// 当たった時の判定
void Shape::OnCollision(bool isHit) {
	isHit_ = isHit;
	if (isHit_) {
		color_ = Math::ColorCodeTransform("#FF181C");
	}
}

// スケールのセッター
void Shape::SetScale(const Vector3 scale) { (void)scale; }

// 回転のセッター
void Shape::SetRotate(const Vector3 rotate) { (void)rotate; }

// 現在位置のセッター
void Shape::SetPosition(const Vector3 translate) { (void)translate; }

// 更新処理
void Shape::Update() {
	if (!isHit_) {
		color_ = Math::ColorCodeTransform("#FFFFFF");
	}
}

// 衝突判定
void Shape::SetIsHit(bool isHit) { isHit_ = isHit; }
