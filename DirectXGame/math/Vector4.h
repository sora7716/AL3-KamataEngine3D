#pragma once
#define WHITE                                                                                                                                                                                          \
	Vector4 { 1.0f, 1.0f, 1.0f, 1.0f }
#define RED                                                                                                                                                                                          \
	Vector4 { 1.0f, 0.0f, 0.0f, 1.0f }
#define BLUE                                                                                                                                                                                          \
	Vector4 { 0.0f, 0.0f, 1.0f, 1.0f }
#define GREEN                                                                                                                                                                                        \
	Vector4 { 0.0f, 1.0f, 0.0f, 1.0f }
#define BLACK                                                                                                                                                                                          \
	Vector4 { 0.0f, 0.0f, 0.0f, 1.0f }
#define DARK_BROWN                                                                                                                                                                                     \
	Vector4 { 0.259f, 0.075f, 0.086f }

/// <summary>
/// 4次元ベクトル
/// </summary>
struct Vector4 final {
	float x;
	float y;
	float z;
	float w;
};