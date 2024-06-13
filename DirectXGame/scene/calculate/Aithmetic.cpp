#include "Aithmetic.h"

MyVector3::MyVector3() {
 vector = {}; }

MyVector3::MyVector3(Vector3 num) {
vector = num; 
}

MyVector3 MyVector3::operator+(const MyVector3& num) {
	Vector3 result{};
	result.x = vector.x + num.vector.x;
	result.y = vector.y + num.vector.y;
	result.z = vector.z + num.vector.z;
	return result;
}

MyVector3& MyVector3::operator+=(const MyVector3& num) {
	// TODO: return ステートメントをここに挿入します
		vector.x += num.vector.x;
		vector.y += num.vector.y;
		vector.z += num.vector.z;
		return *this;
}

MyVector3 MyVector3::operator-(const MyVector3& num) { 
		Vector3 result{};
		result.x = vector.x - num.vector.x;
		result.y = vector.y - num.vector.y;
		result.z = vector.z - num.vector.z;
		return result;
}

MyVector3& MyVector3::operator-=(const MyVector3& num) {
	// TODO: return ステートメントをここに挿入します
		vector.x -= num.vector.x;
		vector.y -= num.vector.y;
		vector.z -= num.vector.z;
		return *this;
}

MyVector3 MyVector3::operator*(float k) {
		MyVector3 result{};
		result.vector.x = vector.x * k;
		result.vector.y = vector.y * k;
		result.vector.z = vector.z * k;
		return result;
}

MyVector3 MyVector3::operator*(const MyVector3& num) {
		Vector3 result{};
		result.x = vector.x * num.vector.x;
		result.y = vector.y * num.vector.y;
		result.z = vector.z * num.vector.z;
		return result;
}

MyVector3& MyVector3::operator/=(float len) {
	// TODO: return ステートメントをここに挿入します
		if (len != 0.0f) {
			vector.x /= len;
			vector.y /= len;
			vector.z /= len;
		}
		return *this;
}


Vector3 MyVector3::GetVector() { return vector; }

void MyVector3::SetVector(Vector3 num) { vector = num; }

Vector3 operator+(const MyVector3& num1, const MyVector3& num2) {
	Vector3 result{};
	result.x = num1.vector.x + num2.vector.x;
	result.y = num1.vector.y + num2.vector.y;
	result.z = num1.vector.z + num2.vector.z;
	return result;
}

Vector3 operator*(const Vector3& vector, const float& num) { 
	Vector3 result = {};
	result.x = vector.x * num;
	result.y = vector.y * num;
	result.z = vector.z * num;
	return result;
}

Vector3 operator+(const MyVector3& vector, const float& num) { 
	Vector3 result;
	result.x = vector.vector.x + num;
	result.y = vector.vector.y + num;
	result.z = vector.vector.z + num;
	return result;
}

Vector3 operator-(const MyVector3& vector1, const MyVector3& vector2) {
	Vector3 result;
	result.x = vector1.vector.x - vector2.vector.x;
	result.y = vector1.vector.y - vector2.vector.y;
	result.z = vector1.vector.z - vector2.vector.z;
	return result;
}

MyMatrix4x4::MyMatrix4x4() { matrix4x4 = {}; }

MyMatrix4x4::MyMatrix4x4(Matrix4x4 num) { matrix4x4 = num; }

MyMatrix4x4 MyMatrix4x4::operator+(const MyMatrix4x4& num) {
	{
		Matrix4x4 result = {};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = matrix4x4.m[i][j] + num.matrix4x4.m[i][j];
			}
		}
		return result;
	}
}

MyMatrix4x4& MyMatrix4x4::operator+=(const MyMatrix4x4& num) {
	// TODO: return ステートメントをここに挿入します
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrix4x4.m[i][j] += num.matrix4x4.m[i][j];
			}
		}
		return *this;
}

MyMatrix4x4 MyMatrix4x4::operator-(const MyMatrix4x4& num) {
		Matrix4x4 result = {};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.m[i][j] = matrix4x4.m[i][j] - num.matrix4x4.m[i][j];
			}
		}
		return result;
}

MyMatrix4x4& MyMatrix4x4::operator-=(const MyMatrix4x4& num) {
	// TODO: return ステートメントをここに挿入します
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrix4x4.m[i][j] -= num.matrix4x4.m[i][j];
			}
		}
		return *this;
}

MyMatrix4x4 MyMatrix4x4::operator*(const MyMatrix4x4& num) {
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

MyMatrix4x4 MyMatrix4x4::operator~() {
	{
		Matrix4x4 result{};
		float determinant = matrix4x4.m[0][0] * (matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] + matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
		                                         matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] - matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
		                                         matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] - matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) -
		                    matrix4x4.m[0][1] * (matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] + matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
		                                         matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] - matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
		                                         matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] - matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) +
		                    matrix4x4.m[0][2] * (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] + matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3] +
		                                         matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] - matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3] -
		                                         matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] - matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) -
		                    matrix4x4.m[0][3] * (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] + matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2] +
		                                         matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] - matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2] -
		                                         matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] - matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]);

		if (determinant != 0) {
			result.m[0][0] =
			    (matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] + matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3] + matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
			     matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3] - matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] - matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			    determinant;

			result.m[0][1] =
			    -(matrix4x4.m[0][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] + matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[0][3] + matrix4x4.m[3][1] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
			      matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[0][3] - matrix4x4.m[2][1] * matrix4x4.m[0][2] * matrix4x4.m[3][3] - matrix4x4.m[0][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			    determinant;

			result.m[0][2] =
			    (matrix4x4.m[0][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] + matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[0][3] + matrix4x4.m[3][1] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			     matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[0][3] - matrix4x4.m[1][1] * matrix4x4.m[0][2] * matrix4x4.m[3][3] - matrix4x4.m[0][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3]) /
			    determinant;

			result.m[0][3] =
			    -(matrix4x4.m[0][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] + matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[0][3] + matrix4x4.m[2][1] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			      matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[0][3] - matrix4x4.m[1][1] * matrix4x4.m[0][2] * matrix4x4.m[2][3] - matrix4x4.m[0][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3]) /
			    determinant;

			result.m[1][0] =
			    -(matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] + matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3] + matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
			      matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3] - matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] - matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			    determinant;

			result.m[1][1] =
			    (matrix4x4.m[0][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] + matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[0][3] + matrix4x4.m[3][0] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
			     matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[0][3] - matrix4x4.m[2][0] * matrix4x4.m[0][2] * matrix4x4.m[3][3] - matrix4x4.m[0][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			    determinant;

			result.m[1][2] =
			    -(matrix4x4.m[0][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] + matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[0][3] + matrix4x4.m[3][0] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			      matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[0][3] - matrix4x4.m[1][0] * matrix4x4.m[0][2] * matrix4x4.m[3][3] - matrix4x4.m[0][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3]) /
			    determinant;

			result.m[1][3] =
			    (matrix4x4.m[0][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] + matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[0][3] + matrix4x4.m[2][0] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			     matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[0][3] - matrix4x4.m[1][0] * matrix4x4.m[0][2] * matrix4x4.m[2][3] - matrix4x4.m[0][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3]) /
			    determinant;

			result.m[2][0] =
			    (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] + matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3] + matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] -
			     matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3] - matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] - matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) /
			    determinant;

			result.m[2][1] =
			    -(matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] + matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[0][3] + matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[2][3] -
			      matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[0][3] - matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[3][3] - matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) /
			    determinant;

			result.m[2][2] =
			    (matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] + matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[0][3] + matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[1][3] -
			     matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[0][3] - matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[3][3] - matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3]) /
			    determinant;

			result.m[2][3] =
			    -(matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] + matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[0][3] + matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[1][3] -
			      matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[0][3] - matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[2][3] - matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3]) /
			    determinant;

			result.m[3][0] =
			    -(matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] + matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2] + matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] -
			      matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2] - matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] - matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]) /
			    determinant;

			result.m[3][1] =
			    (matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] + matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[0][2] + matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[2][2] -
			     matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[0][2] - matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[3][2] - matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]) /
			    determinant;

			result.m[3][2] =
			    -(matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] + matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[0][2] + matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[1][2] -
			      matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[0][2] - matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[3][2] - matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2]) /
			    determinant;

			result.m[3][3] =
			    (matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] + matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[0][2] + matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[1][2] -
			     matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[0][2] - matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[2][2] - matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2]) /
			    determinant;
		}

		return result;
	}
}

Matrix4x4 MyMatrix4x4::GetMatrix4x4() { return matrix4x4; }

void MyMatrix4x4::SetMatrix4x4(Matrix4x4 num) { matrix4x4 = num; }

Vector3 Lerp(Vector3 translate, MyVector3 goal, float time) { 
	Vector3 result = {};
	result.x = (translate.x* time) + goal.vector.x * (1 - time); 
	result.y = (translate.y* time) + goal.vector.y * (1 - time); 
	result.z = (translate.z* time) + goal.vector.z * (1 - time); 
	return result;
}
