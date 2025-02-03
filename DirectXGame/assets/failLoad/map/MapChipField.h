#pragma once
#define _USE_MATH_DEFINES
#include "Vector3.h"
#include <cmath>
#include <string>
#include <vector>
using namespace std;

enum class MapChipType {
	kBlank, // 空白
	kBlock  // ブロック
};

typedef struct MapChipData {
	vector<vector<MapChipType>> data;
} MapChipData;

class MapChipField {
public: // メンバ関数
	typedef struct IndexSet {
		uint32_t xIndex;
		uint32_t zIndex;
	} IndexSet;

	/// <summary>
	/// マップチップのリセット
	/// </summary>
	void ResetMapChipData();

	/// <summary>
	/// マップチップの読み込み
	/// </summary>
	/// <param name="filePath">ファイル名</param>
	void LoadMapChipCsv(const std::string& filePath);

	/// <summary>
	/// マップチップ種別の取得
	/// </summary>
	/// <param name="xIndex">x</param>
	/// <param name="yIndex">y</param>
	/// <returns></returns>
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	/// <summary>
	/// マップ番号のゲッター{x,z}
	/// </summary>
	/// <param name="position">現在の位置</param>
	/// <returns>マップ番号{x,z}</returns>
	IndexSet GetMapChipNumber(const Vector3& position);

public: // 静的メンバ変数
	// 1ブロックのサイズ
	static inline const Vector3 kHexagonRadius = {10.0f,3.0f,10.0f};
	// ブロックのサイズ
	static inline const uint32_t kNumBlockVertical = 10;
	static inline const uint32_t kNumBlockHorizontal = 10;

private: // メンバ変数
	// マップチップのデータ
	MapChipData mapChipData_;
};
