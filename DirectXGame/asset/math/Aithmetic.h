#pragma once
#include <Matrix4x4.h>
#include <Vector3.h>
#include <vector>
#include <list>
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>
#include <algorithm>
#include <cassert>

/// <summary>
/// 加算
/// </summary>
/// <param name="num1"></param>
/// <param name="num2"></param>
/// <returns></returns>
const Vector3 operator+(const Vector3& num1, const Vector3& num2);

/// <summary>
/// 加算(複合)
/// </summary>
/// <param name="num1"></param>
/// <param name="num2"></param>
/// <returns></returns>
const Vector3& operator+=(Vector3& num1, const Vector3& num2);

/// <summary>
/// 減算
/// </summary>
/// <param name="num1"></param>
/// <param name="num2"></param>
/// <returns></returns>
const Vector3 operator-(const Vector3& num1, const Vector3& num2);

/// <summary>
/// 減算(複合)
/// </summary>
/// <param name="num1"></param>
/// <param name="num2"></param>
/// <returns></returns>
const Vector3& operator-=(Vector3& num1, const Vector3& num2);

/// <summary>
/// スカラー倍
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Vector3 operator*(const Vector3& num, const float& k);

/// <summary>
/// スカラー倍(複合)
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Vector3& operator*=(Vector3& num, const float& k);

/// <summary>
/// 掛け算
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Vector3 operator*(const Vector3& num1, const Vector3& num2);

/// <summary>
/// 掛け算(複合)
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Vector3& operator*=(Vector3& num1, const Vector3& num2);

/// <summary>
/// 割り算(float と Vector3の複合)
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Vector3& operator/=(Vector3& num, const float& len);

/// <summary>
/// 割り算(float と Vector3)
/// </summary>
/// <param name="num"></param>
/// <param name="len"></param>
/// <returns></returns>
const Vector3 operator/(const Vector3& num, const float& len);

/// <summary>
/// スカラー倍(float*Vector3)
/// </summary>
/// <param name="num1"></param>
/// <param name="num2"></param>
/// <returns></returns>
const Vector3 operator*(const float& num1, const Vector3& num2);

/// <summary>
/// 加法(Vector3とfloat)
/// </summary>
/// <param name="v"></param>
/// <param name="num"></param>
/// <returns></returns>
const Vector3& operator+=(Vector3& v, const float& num);

/// <summary>
/// 除法
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns></returns>
const Vector3 operator/(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 加算
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Matrix4x4 operator+(const Matrix4x4& num1, const Matrix4x4& num2);

/// <summary>
/// ベクトルと行列の掛け算
/// </summary>
/// <param name="v">ベクトル</param>
/// <param name="m">行列</param>
/// <returns></returns>
const Vector3 operator*(const Vector3& v, const Matrix4x4& m);

/// <summary>
/// 加算(複合)
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Matrix4x4& operator+=(Matrix4x4& num1, const Matrix4x4& num2);

/// <summary>
/// 減算
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Matrix4x4 operator-(const Matrix4x4& num1, const Matrix4x4& num2);

/// <summary>
/// 減算(複合)
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Matrix4x4& operator-=(Matrix4x4& num1, const Matrix4x4& num2);

/// <summary>
/// 掛け算
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Matrix4x4 operator*(const Matrix4x4& num1, const Matrix4x4& num2);

/// <summary>
/// 掛け算(*=)
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Matrix4x4 operator*=(const Matrix4x4& num1, const Matrix4x4& num2);

/// <summary>
/// 逆行列
/// </summary>
/// <returns></returns>
const Matrix4x4 operator~(const Matrix4x4& num);

/// <summary>
/// 行列と浮動小数の掛け算
/// </summary>
/// <param name="m">行列</param>
/// <param name="num">浮動小数</param>
/// <returns>行列</returns>
const Matrix4x4 operator*(const Matrix4x4 m, float num);
