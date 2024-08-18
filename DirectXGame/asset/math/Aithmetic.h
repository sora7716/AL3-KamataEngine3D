#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>

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
const Vector3 operator* (const float& num1, const Vector3& num2);

//加法(Vector3とfloat)
const Vector3& operator+=(Vector3& v, const float& num);

/// <summary>
/// 加算
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
const Matrix4x4 operator+(const Matrix4x4& num1,const Matrix4x4& num2);

/// <summary>
///加算(複合) 
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
/// 逆行列
/// </summary>
/// <returns></returns>
const Matrix4x4 operator~(const Matrix4x4& num);

