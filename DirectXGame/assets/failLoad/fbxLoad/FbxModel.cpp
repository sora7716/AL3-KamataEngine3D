#include "FbxModel.h"
#include <iostream>

// コンストラクタ
FbxLoad::FbxLoad() {
	manager_ = FbxManager::Create();
	ios_ = FbxIOSettings::Create(manager_, IOSROOT);
	manager_->SetIOSettings(ios_);
}

// デストラクタ
FbxLoad::~FbxLoad() {
	// リソースのクリーンアップ
	if (manager_) {
		manager_->Destroy();
		manager_ = nullptr;
	}
}

// FBXファイルのロード
FbxScene* FbxLoad::Load(const char* filename) {
	// インポーターを作成
	FbxImporter* importer = FbxImporter::Create(manager_, "");

	// ファイルの初期化とインポーター
	if (!importer->Initialize(filename, -1, manager_->GetIOSettings())) {
		std::cerr << "FBX　ファイルの初期化に失敗しました" << importer->GetStatus().GetErrorString() << std::endl;
		return nullptr;
	}

	// シーンの作成
	FbxScene*scene = FbxScene::Create(manager_, "scene");
	importer->Import(scene);
	importer->Destroy();

	return scene;
}

// ノードを再帰的に処理し、メッシュを取得
void FbxLoad::ProcessNode(FbxNode* node, std::vector<FbxMesh*> meshes) {
	if (!node) {
		return;
	}
	FbxNodeAttribute* attribute = node->GetNodeAttribute();
	if (attribute) {
		if (attribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
			meshes.push_back(node->GetMesh());
		}
	}
	for (int i = 0; i < node->GetChildCount(); ++i) {
		ProcessNode(node->GetChild(i), meshes);
	}
}

// メッシュデータの取得
std::vector<Vertex> FbxLoad::GetMeshData(FbxMesh* mesh) {
	std::vector<Vertex> vertices;
	int polygonCount = mesh->GetPolygonCount();

	for (int i = 0; i < polygonCount; i++) {
		for (int j = 0; j < 3; j++) { // 各ポリゴンの頂点
			int controlPointIndex = mesh->GetPolygonVertex(i, j);
			FbxVector4 vertex = mesh->GetControlPointAt(controlPointIndex);
			FbxVector4 normal;
			mesh->GetPolygonVertexNormal(i, j, normal);
			// 頂点データを構造体に格納
			Vertex v = {
			    static_cast<float>(vertex[0]),
			    static_cast<float>(vertex[1]),
			    static_cast<float>(vertex[2]),
			    static_cast<float>(normal[0]),
			    static_cast<float>(normal[1]),
			    static_cast<float>(normal[2]),
			    0.0f, // UV座標は適宜設定
			    0.0f};
			vertices.push_back(v);
		}
	}
	return vertices;
}

// 頂点バッファの作成
void FbxLoad::CreateVertexBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<Vertex>& vertices) {
	// 頂点バッファのサイズ
	const UINT vertexBufferSize = static_cast<UINT>(vertices.size() * sizeof(Vertex));
	// 頂点バッファのリソースを作成
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);

	ID3D12Resource* vertexBuffer;
	device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexBuffer));

	// 頂点バッファに書き込む
	UINT8* pVertexDataBegin;
	CD3DX12_RANGE readRange(0, 0);
	vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
	memcpy(pVertexDataBegin, vertices.data(), vertexBufferSize);
	vertexBuffer->Unmap(0, nullptr);

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.StrideInBytes = sizeof(Vertex);
	vertexBufferView.SizeInBytes = vertexBufferSize;

	// コマンドリストに頂点バッファをバインド
	commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
	this->vertices_ = vertices; // 頂点データをクラスメンバーに格納
}

// 描画
void FbxLoad::Render(ID3D12GraphicsCommandList* commandList) {
	// パイプラインステートの設定
	commandList->SetPipelineState(pipelineState.Get());
	// プリミティブの種類を設定(三角形リストなど)
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 描画コマンドの発行
	commandList->DrawInstanced(static_cast<UINT>(vertices_.size()), 1, 0, 0);
}
