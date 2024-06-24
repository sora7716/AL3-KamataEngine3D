#include "MapChipField.h"
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>
namespace {
  //連想配列
  map<string, MapChipType> mapChipTable = {
      {"0", MapChipType::kBlank},//文字列の0が変えてきたらkBlankを返す
      {"1", MapChipType::kBlock},
  };
}//どこのnamespaceに属していない

  // マップチップデータのリセット
  void MapChipField::ResetMapChipData() { 
      mapChipData_.data.clear();
      mapChipData_.data.resize(kNumBlockVertical);
	  for (vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		  mapChipDataLine.resize(kNumBlockHorizontal);	  
      }
  }

  void MapChipField::LoadMapChipCsv(const std::string& filePath) { 
      //マップチップデータのリセット
      ResetMapChipData();
      //ファイルを開く
      ifstream file;//1行ずつ読み込む(すべてを一気に読み込むわけではない)
	  file.open(filePath);
	  assert(file.is_open());

      //マップチップCSV
	  stringstream mapChipCsv;//1文字ずつ読み込んでいく

      //ファイルの内容を文字列ストリームにコピー
	  mapChipCsv << file.rdbuf();//文字のコピーをfileに入れていく

      //ファイルを閉じる
	  file.close();
	  
      //CSVからマップチップデータを読み込む
	  for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
		  string line;
		  getline(mapChipCsv, line);
          //1行分の文字列をストリームに変換して解析しやすくする
          istringstream line_stream(line);//文字列のstram

          for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			  string word;
			  getline(line_stream, word, ',');//','(区切り文字),word(1文字)
			  if (mapChipTable.contains(word)) {//getlineからwordに文字を読み込んでその文字が連想配列に存在しているか
				  mapChipData_.data[i][j] = mapChipTable[word];//連想配列
              }
          }
      }
  }

  //マップチップ種別の取得
  MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	  //配列外参照された場合に空白を返すことで安全性を高めてる
      if (xIndex< 0 || kNumBlockHorizontal - 1 < xIndex) {
		  return MapChipType ::kBlank;
      }
	  if (yIndex < 0 || kNumBlockVertical - 1 < yIndex) {
		  return MapChipType::kBlank;
      }
	  return mapChipData_.data[yIndex][xIndex];
  }

  //マップチップ座標の取得
  Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { 
  
	  return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVertical - 1 - yIndex), 0);   //(kNumBlockVirtical - 1 - yIndex)をすることで2次元配列の上下を反転させている
  
  }

  MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position) {
	  IndexSet result;
	  int mapIndexY = kNumBlockVertical - 1;
	  result.xIndex = static_cast<uint32_t>((position.x + kBlockWidth / 2.0f) / kBlockWidth);
	  uint32_t yIndex = static_cast<uint32_t>((position.y + kBlockHeight / 2.0f) / kBlockHeight);
	  result.yIndex = static_cast<uint32_t>(mapIndexY - yIndex);
	  return result;
  }

  MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	  Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);
	  Rect rect;
	  rect.left   = center.x - kBlockWidth / 2.0f;
	  rect.right  = center.x + kBlockWidth / 2.0f;
	  rect.bottom = center.y - kBlockHeight / 2.0f;
	  rect.top    = center.y + kBlockHeight / 2.0f;
	  return rect;
  }
