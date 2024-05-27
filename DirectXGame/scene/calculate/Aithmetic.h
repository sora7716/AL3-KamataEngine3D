#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>

class MyVector3{
public:
	/// <summary>
	/// デフォルトコンストラクター
	/// </summary>
	MyVector3() {
		vector = {};
	}

	/// <summary>
	/// コンストラクター
	/// </summary>
	/// <param name="num">xyzの座標</param>
	MyVector3(Vector3 num) {
		vector = num;
	}

	/// <summary>
	/// 足し算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator+(const MyVector3& num) {
		MyVector3 result{};
		result.vector.x = vector.x + num.vector.x;
		result.vector.y = vector.y + num.vector.y;
		result.vector.z = vector.z + num.vector.z;
		return result;
	}

	/// <summary>
	/// 足し算(複合)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3& operator+=(const MyVector3& num) {
		vector.x += num.vector.x;
		vector.y += num.vector.y;
		vector.z += num.vector.z;
		return *this;
	}

	/// <summary>
	/// 引き算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator-(const MyVector3& num) {
		MyVector3 result{};
		result.vector.x = vector.x - num.vector.x;
		result.vector.y = vector.y - num.vector.y;
		result.vector.z = vector.z - num.vector.z;
		return result;
	}

	/// <summary>
	/// 引き算(複合)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3& operator-=(const MyVector3& num) {
		vector.x -= num.vector.x;
		vector.y -= num.vector.y;
		vector.z -= num.vector.z;
		return *this;
	}

	/// <summary>
	/// スカラー倍
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator*(float k) {
		MyVector3 result{};
		result.vector.x = vector.x * k;
		result.vector.y = vector.y * k;
		result.vector.z = vector.z * k;
		return result;
	}

	/// <summary>
	/// 掛け算(ベクトル同士)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3 operator*(const MyVector3& num) {
		MyVector3 result{};
		result.vector.x = vector.x * num.vector.x;
		result.vector.y = vector.y * num.vector.y;
		result.vector.z = vector.z * num.vector.z;
		return result;
	}

	/// <summary>
	/// 単位ベクトル
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyVector3& operator/=(float len) {
		if (len != 0.0f) {
			vector.x /= len;
			vector.y /= len;
			vector.z /= len;
		}
		return *this;
	}

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetVector() { return vector; };

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="num"></param>
	void SetVector(Vector3 num) {
		vector = num;
	}

private:
	Vector3 vector;
};

class MyMatrix4x4 {
public:

	/// <summary>
	/// デフォルトコンストラクター
	/// </summary>
	MyMatrix4x4() {
		matrix4x4 = {};
	}

	/// <summary>
	/// コンストラクター
	/// </summary>
	/// <param name="num"></param>
	MyMatrix4x4(Matrix4x4 num) {
		matrix4x4 = num;
	}

	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4 operator+(const MyMatrix4x4& num) {
		Matrix4x4 result = {};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = matrix4x4.m[i][j] + num.matrix4x4.m[i][j];
			}
		}
		return result;
	}

	/// <summary>
	///加算(複合) 
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4& operator+=(const MyMatrix4x4& num) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrix4x4.m[i][j] += num.matrix4x4.m[i][j];
			}
		}
		return *this;
	}

	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4 operator-(const MyMatrix4x4& num) {
		Matrix4x4 result = {};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = matrix4x4.m[i][j] - num.matrix4x4.m[i][j];
			}
		}
		return result;
	}

	/// <summary>
	/// 減算(複合)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4& operator-=(const MyMatrix4x4& num) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
			 matrix4x4.m[i][j] -= num.matrix4x4.m[i][j];
			}
		}
		return *this;
	}

	/// <summary>
	/// 掛け算
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	MyMatrix4x4 operator*(const MyMatrix4x4& num) {
		Matrix4x4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = 0;
				for (int k = 0; k < 4; k++) {
					result.m[i][j] += matrix4x4.m[i][k] * num.matrix4x4.m[k][j];
				}
			}
		}
		return result;
	}

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <returns></returns>
	MyMatrix4x4 operator~() {
		Matrix4x4 result{};
		float determinant = matrix4x4.m[0][0] * (matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
			matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
			matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
			matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
			matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
			matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) -
			matrix4x4.m[0][1] * (matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
				matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
				matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
				matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
				matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
				matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) +
			matrix4x4.m[0][2] * (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] +
				matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3] +
				matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] -
				matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3] -
				matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] -
				matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) -
			matrix4x4.m[0][3] * (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] +
				matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2] +
				matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] -
				matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2] -
				matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] -
				matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]);



		if (determinant != 0) {
			result.m[0][0] = (matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
				matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
				matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
				matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
				matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
				matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
				determinant;

			result.m[0][1] = -(matrix4x4.m[0][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
				matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
				matrix4x4.m[3][1] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
				matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[0][3] -
				matrix4x4.m[2][1] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
				matrix4x4.m[0][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
				determinant;

			result.m[0][2] = (matrix4x4.m[0][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] +
				matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
				matrix4x4.m[3][1] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
				matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
				matrix4x4.m[1][1] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
				matrix4x4.m[0][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3]) /
				determinant;

			result.m[0][3] = -(matrix4x4.m[0][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] +
				matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[0][3] +
				matrix4x4.m[2][1] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
				matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
				matrix4x4.m[1][1] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
				matrix4x4.m[0][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3]) /
				determinant;


			result.m[1][0] = -(matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
				matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
				matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
				matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
				matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
				matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
				determinant;

			result.m[1][1] = (matrix4x4.m[0][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
				matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
				matrix4x4.m[3][0] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
				matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[0][3] -
				matrix4x4.m[2][0] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
				matrix4x4.m[0][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
				determinant;

			result.m[1][2] = -(matrix4x4.m[0][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] +
				matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
				matrix4x4.m[3][0] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
				matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
				matrix4x4.m[1][0] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
				matrix4x4.m[0][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3]) /
				determinant;

			result.m[1][3] = (matrix4x4.m[0][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] +
				matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[0][3] +
				matrix4x4.m[2][0] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
				matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
				matrix4x4.m[1][0] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
				matrix4x4.m[0][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3]) /
				determinant;


			result.m[2][0] = (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] +
				matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3] +
				matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] -
				matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3] -
				matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] -
				matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) /
				determinant;

			result.m[2][1] = -(matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] +
				matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[0][3] +
				matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[2][3] -
				matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[0][3] -
				matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[3][3] -
				matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) /
				determinant;

			result.m[2][2] = (matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] +
				matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[0][3] +
				matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[1][3] -
				matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[0][3] -
				matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[3][3] -
				matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3]) /
				determinant;

			result.m[2][3] = -(matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] +
				matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[0][3] +
				matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[1][3] -
				matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[0][3] -
				matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[2][3] -
				matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3]) /
				determinant;

			result.m[3][0] = -(matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] +
				matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2] +
				matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] -
				matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2] -
				matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] -
				matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]) /
				determinant;

			result.m[3][1] = (matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] +
				matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[0][2] +
				matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[2][2] -
				matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[0][2] -
				matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[3][2] -
				matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]) /
				determinant;

			result.m[3][2] = -(matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] +
				matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[0][2] +
				matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[1][2] -
				matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[0][2] -
				matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[3][2] -
				matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2]) /
				determinant;

			result.m[3][3] = (matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] +
				matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[0][2] +
				matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[1][2] -
				matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[0][2] -
				matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[2][2] -
				matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2]) /
				determinant;
		}

		return result;
	}


	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns>matrix4x4</returns>
	Matrix4x4 GetMatrix4x4() { return matrix4x4; };

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="num"></param>
	void SetMatrix4x4(Matrix4x4 num) {
		matrix4x4 = num;
	}

private:
	Matrix4x4 matrix4x4;
};

