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
		uint32_t yIndex;
	} Index;

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
public: // 静的メンバ変数
	// 1ブロックのサイズ
	static inline const float kHexagonRadius = 1.0f;
	// ブロックのサイズ
	static inline const uint32_t kNumBlockVertical = 8;
	static inline const uint32_t kNumBlockHorizontal = 8;

private: // メンバ変数
	// マップチップのデータ
	MapChipData mapChipData_;
};
