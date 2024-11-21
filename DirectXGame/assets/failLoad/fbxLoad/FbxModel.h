#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_4.h>
#include <fbxsdk.h>
#include <stdexcept>
#include <vector>
#include <wrl.h>

// 頂点構造体
struct Vertex {
	float x, y, z;
	float nx, ny, nz;
	float u, v;
};

/// <summary>
/// FBXのモデル
/// </summary>
class FbxLoad {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FbxLoad();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FbxLoad();

	/// <summary>
	/// FBXファイルのロード
	/// </summary>
	/// <param name="filename">FBXファイルの名前</param>
	/// <returns>FBX</returns>
	FbxScene* Load(const char* filename);

	/// <summary>
	/// ノードを再帰的に処理し、メッシュを取得
	/// </summary>
	/// <param name="node">ノード</param>
	/// <param name="meshes">メッシュ</param>
	void ProcessNode(FbxNode* node, std::vector<FbxMesh*> meshes);

	/// <summary>
	/// メッシュデータの取得
	/// </summary>
	/// <param name="mesh">メッシュ</param>
	/// <returns>メッシュデータ</returns>
	std::vector<Vertex> GetMeshData(FbxMesh* mesh);

	/// <summary>
	/// 頂点バッファの作成
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="commandList">コマンドリスト</param>
	/// <param name="vertices">頂点</param>
	void CreateVertexBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<Vertex>& vertices);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="commandList">コマンドリスト</param>
	void Render(ID3D12GraphicsCommandList*commandList);

private: // メンバ変数
	FbxManager* manager_;
	FbxIOSettings* ios_;
	// パイプラインステートオブジェクト
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	// 頂点データ
	std::vector<Vertex> vertices_; 
};
