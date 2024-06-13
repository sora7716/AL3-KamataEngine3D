#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <string>
#include "Vector3.h"
using namespace std;

enum class MapChipType {
	kBlank, // 空白
	kBlock  // ブロック
};



typedef struct MapChipData {
	vector<vector<MapChipType>> data;
} MapChipData;

class MapChipField {
public:

	typedef struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	} IndexSet;

	// 範囲矩形
	typedef struct Rect {
		float left;
		float right;
		float bottom;
		float top;
	} Rect;

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
	/// マップチップ座標の取得
	/// </summary>
	/// <param name="xIndex">x</param>
	/// <param name="yIndex">y</param>
	/// <returns></returns>
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	/// <summary>
	/// マップチップの縦幅のゲッター
	/// </summary>
	/// <returns>kNumBlockVertical</returns>
	uint32_t GetNumBlockVertical() { return kNumBlockVertical; };

	/// <summary>
	/// マップチップの横幅のゲッター
	/// </summary>
	/// <returns>kNumBlockHorizontal</returns>
	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; };

	/// <summary>
	/// マップチップのポジションのゲッター
	/// </summary>
	/// <param name="position">プレイヤーのポジション</param>
	/// <returns>マップチップの番号</returns>
	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	/// <summary>
	/// 各頂点のゲッター
	/// </summary>
	/// <param name="index">x,yの座標</param>
	/// <returns>矩形の頂点</returns>
	Rect GetRectByIndex(const IndexSet& index);

private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth  = 2.0f;
	static inline const float kBlockHeight = 2.0f;
	// ブロックのサイズ
	static inline const uint32_t kNumBlockVertical   = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
    //マップチップのデータ
	MapChipData mapChipData_;
};
