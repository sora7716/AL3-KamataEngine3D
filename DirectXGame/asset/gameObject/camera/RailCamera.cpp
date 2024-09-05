#include "RailCamera.h"
#include "PrimitiveDrawer.h"
#include "asset/math/Math.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG


// 初期化
void RailCamera::Initialize(const Matrix4x4& matWorld, const Vector3& radian, const ViewProjection* viewProjection) {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.matWorld_ = matWorld;                         // ワールド座標を設定
	worldTransform_.rotation_ = radian;                           // 回転角を設定
	worldTransform_.translation_ = Vector3({0.0f, 0.0f, 0.0f}); // カメラの初期位置を設定
	// ビュープロジェクションの初期化
	viewProjection_.farZ = 20000;
	viewProjection_.Initialize();

	// 制御点の初期化
	controlPoints_ = {
	    {0,  0,  0}, // 開始点
	    {10, 5,  0}, // 小さなカーブ1
	    {20, 10, 0}, // 直線部分
	    {30, 20, 0}, // 大きなカーブ
	    {40, 15, 0}, // 高さを下げる
	    {50, 20, 5}, // Z軸の変化
	    {60, 10, 0}, // 高さを戻す
	    {70, 25, 0}, // 直線部分
	    {80, 30, 0}  // 最後の点、終了点
	};



	controlPoints_.push_back(controlPoints_.front());

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(viewProjection);
}

// 更新
void RailCamera::Update() {
	//t_ += 1.0f/1000.0f;
	//if (t_ > 1.0f) {
	//	t_ -= 1.0f; // t が 1.0f を超えたらループさせる
	//}
	// 移動
	//worldTransform_.translation_ = Math::CatmullRomPosition(controlPoints_, t_);
	//worldTransform_.rotation_ = Math::CatmullRomPosition(controlPoints_, t_);
	
	// ワールド行列を再計算
	worldTransform_.UpdateMatrix();
	// カメラのオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = ~worldTransform_.matWorld_;

	#ifdef _DEBUG
	// カメラの座標を画面に表示する処理
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::Text("t%f", t_);
	ImGui::End();
#endif // _DEBUG

	
}

// カメラの起動
void RailCamera::Draw() {
	// 曲線で描画する用の頂点リスト
	std::vector<Vector3> pointsDrawing;
	// 線分の数
	const size_t segmentCount = 100;
	// 線分の数+1個分の頂点座標を計算
	for (size_t i = 0; i < segmentCount + 1; i++) {
		float t = 1.0f / segmentCount * i;
		Vector3 pos = Math::CatmullRomPosition(controlPoints_, t);
		// 描画用語頂点リストに追加
		pointsDrawing.push_back(pos);
	}

	// 描画
	for (size_t i = 0; i < segmentCount; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(pointsDrawing[i], pointsDrawing[i + 1], {1.0f, 0.0f, 0.0f, 1.0f});
	}
}

// ビュープロジェクションのゲッター
const ViewProjection& RailCamera::GetViewProjection() const {
	// TODO: return ステートメントをここに挿入します
	return viewProjection_;
}

// ワールドトランスフォームのゲッター
const WorldTransform& RailCamera::GetWorldTransform() const {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// トランスレイションのセッター
void RailCamera::SetTranslation(Vector3 translation) { worldTransform_.translation_ = translation; }

// ローテションのセッター
void RailCamera::SetRotation(Vector3 rotation) { worldTransform_.rotation_ = rotation; }
