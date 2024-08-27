#include "Math.h"
#include <cassert>
#include <cmath>
#include <algorithm>
#define cont(theta) (1.0f / tanf(theta))
using namespace std;

// 転置行列
Matrix4x4 Math::Transpose(Matrix4x4 m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}

	return result;
}

// 単位行列
Matrix4x4 Math::MakeIdentity4x4() {
	Matrix4x4 result{
	    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	return result;
}

// 拡縮
Matrix4x4 Math::MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{scale.x, 0.0f, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 0.0f, scale.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return result;
}

// 平行移動
Matrix4x4 Math::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translate.x, translate.y, translate.z, 1.0f};
	return result;
}

// 同次座標系で計算しデカルト座標系に変換
Vector3 Math::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	// assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

// x座標を軸に回転
Matrix4x4 Math::MakeRotateXMatrix(const float& radian) {
	Matrix4x4 result{
	    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos(radian), sin(radian), 0.0f, 0.0f, -sin(radian), cos(radian), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	return result;
}

// y座標を軸に回転
Matrix4x4 Math::MakeRotateYMatrix(const float& radian) {
	Matrix4x4 result{cos(radian), 0.0f, -sin(radian), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sin(radian), 0.0f, cos(radian), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return result;
}

// z座標を軸に回転
Matrix4x4 Math::MakeRotateZMatrix(const float& radian) {
	Matrix4x4 result{cos(radian), sin(radian), 0.0f, 0.0f, -sin(radian), cos(radian), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return result;
}

// x,y,z座標で回転
Matrix4x4 Math::MakeRotateXYZMatrix(const Vector3& radian) { return MakeRotateXMatrix(radian.x) * MakeRotateYMatrix(radian.y) * MakeRotateZMatrix(radian.z); }

// アフィン関数
Matrix4x4 Math::MakeAffineMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate) {
	return (MakeScaleMatrix(scale) * MakeRotateXYZMatrix(radian)) * MakeTranslateMatrix(translate);
}

// STRの変換
Matrix4x4 Math::MakeSTRMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate) { return MakeScaleMatrix(scale) * MakeTranslateMatrix(translate) * MakeRotateXYZMatrix(radian); }

// 正射影行列
Matrix4x4 Math::MakeOrthographicMatrix(const float& left, const float& top, const float& right, const float& bottom, const float& nearClip, const float& farClip) {
	Matrix4x4 result{
	    2.0f / (right - left),
	    0.0f,
	    0.0f,
	    0.0f,
	    0.0f,
	    2.0f / (top - bottom),
	    0.0f,
	    0.0f,
	    0.0f,
	    0.0f,
	    1.0f / (farClip - nearClip),
	    0.0f,
	    (left + right) / (left - right),
	    (top + bottom) / (bottom - top),
	    nearClip / (nearClip - farClip),
	    1.0f};

	return result;
}

// 透視投影行列
Matrix4x4 Math::MakePerspectiveFovMatrix(const float& fovY, const float& aspectRation, const float& nearClip, const float& farClip) {
	Matrix4x4 result{1.0f / aspectRation * cont(fovY / 2.0f),      0.0f, 0.0f, 0.0f, 0.0f, cont(fovY / 2.0f), 0.0f, 0.0f, 0.0f, 0.0f, farClip / (farClip - nearClip), 1.0f, 0.0f, 0.0f,
	                 -(nearClip * farClip) / (farClip - nearClip), 0.0f};

	return result;
}

// ビューポートマトリックス
Matrix4x4 Math::MakeViewportMatrix(const float& left, const float& top, const float& width, const float& height, const float& minDepth, const float& maxDepth) {
	Matrix4x4 result{
	    width / 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, -height / 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, maxDepth - minDepth, 0.0f, (left + width) / 2.0f, (top + height) / 2.0f, minDepth, 1.0f,
	};
	return result;
}

// クロス積
Vector3 Math::Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

// 内積
float Math::Dot(const Vector3& v1, const Vector3& v2) {
 return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// ノルム
float Math::Length(const Vector3& v) {
	Vector3 result = {};
	result = v * v;
	float length = sqrtf(result.x + result.y + result.z);
	return length;
}

// 単位ベクトル
Vector3 Math::Normalize(const Vector3& v) {
	float len = Length(v);
	if (len != 0.0f) {
		return v / len;
	}
	return Vector3{0.0f, 0.0f, 0.0f}; // 長さが0の場合
}

// 正規化
float Math::Normalize(const float& num) {
	float len = powf(num, 2);
	if (len != 0.0f) {
		float result = num / len;
		return result;
	}
	return num;
}

// トランスフォームノーマル
Vector3 Math::TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
	return result;
}

//線形補間
Vector3 Math::Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;
	result.x = v1.x + t * (v2.x - v1.x);
	result.y = v1.y + t * (v2.y - v1.y);
	result.z = v1.z + t * (v2.z - v1.z);

	return result;
}

//線形補間
float Math::Lerp(const float& num1, const float& num2, float t) { 
	float result;
	result= num1 + t * (num2 - num1); 
	return result;
}

Vector3 Math::SLerp(const Vector3& v1, const Vector3& v2, float t) { 
	//v1の正規化ベクトル
	Vector3 nv1 = Normalize(v1); 
	//v2の正規化ベクトルを求める
	Vector3 nv2 = Normalize(v2);
	//内積を求める
	float dot = Dot(v1, v2);
	//誤差により1.0fを超えるのを防ぐ
	dot = clamp(dot, -1.0f, 1.0f);
	//アークコサインでθの角度を求める
	float theta = acos(dot);
	//θの角度からsinθを求める
	float sinTheta = sin(theta);
	//サイン(θ(1-t))を求める
	float sinThetaFrom = sin((1 - t) * theta);
	//サインθtを求める
	float sinThetaTo = sin(t + theta);

	Vector3 normalizeVector;
	//ゼロ除算を防ぐ
	if (sinTheta < 1.0e-5) {
		normalizeVector = v1;
	} else {
	//球面線形保管したベクトル(単位ベクトル)
		normalizeVector = sinThetaFrom / sinTheta * nv1 + sinThetaTo / sinTheta * v2;
	}
	//ベクトルの長さはv1とv2の長さを線形補間
	float length1 = Length(v1);
	float length2 = Length(v2);
	//Lerpで補間ベクトルの長さを求める
	float length = Lerp(length1, length2, t);
	return length * normalizeVector;
}
