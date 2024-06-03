#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>

class MyVector3{
public:
	/// <summary>
	/// デフォルトコンストラクター
	/// </summary>
	MyVector3();

	/// <summary>
	/// コンストラクター
	/// </summary>
	/// <param name="num">xyzの座標</param>
	MyVector3(Vector3 num);

	/// <summary>
	/// 足し算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator+(const MyVector3& num);

	/// <summary>
	/// 足し算(複合)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3& operator+=(const MyVector3& num);

	/// <summary>
	/// 引き算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator-(const MyVector3& num);

	/// <summary>
	/// 引き算(複合)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3& operator-=(const MyVector3& num);

	/// <summary>
	/// スカラー倍
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator*(float k);

	/// <summary>
	/// 掛け算(ベクトル同士)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator*(const MyVector3& num);

	/// <summary>
	/// 単位ベクトル
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3& operator/=(float len);

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetVector();

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="num"></param>
	void SetVector(Vector3 num);

public:
	Vector3 vector;
};

class MyMatrix4x4 {
public:

	/// <summary>
	/// デフォルトコンストラクター
	/// </summary>
	MyMatrix4x4();

	/// <summary>
	/// コンストラクター
	/// </summary>
	/// <param name="num"></param>
	MyMatrix4x4(Matrix4x4 num);

	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4 operator+(const MyMatrix4x4& num);

	/// <summary>
	///加算(複合) 
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4& operator+=(const MyMatrix4x4& num);

	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4 operator-(const MyMatrix4x4& num);

	/// <summary>
	/// 減算(複合)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4& operator-=(const MyMatrix4x4& num); 

	/// <summary>
	/// 掛け算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4 operator*(const MyMatrix4x4& num);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <returns></returns>
	MyMatrix4x4 operator~();


	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns>matrix4x4</returns>
	Matrix4x4 GetMatrix4x4();

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="num"></param>
	void SetMatrix4x4(Matrix4x4 num);

public:
	Matrix4x4 matrix4x4;
};


/// <summary>
/// 足し算(二つの場合)
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
MyVector3 operator+(const MyVector3& num1, const MyVector3& num2);

Vector3 Lerp(Vector3 translate, MyVector3 goal, float time);