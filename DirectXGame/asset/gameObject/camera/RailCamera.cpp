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
	worldTransform_.matWorld_ = matWorld;                       // ワールド座標を設定
	worldTransform_.rotation_ = radian;                         // 回転角を設定
	worldTransform_.translation_ = Vector3({0.0f, 0.0f, 0.0f}); // カメラの初期位置を設定
	// ビュープロジェクションの初期化
	viewProjection_.farZ = 20000;
	viewProjection_.Initialize();

	// 制御点の初期化
	controlPoints_ = {
	    {0.0f,  0.0f,    20.0f }, // 開始点
	    {5.0f,  -10.0f,  15.0f }, // 初期の緩やかな下降
	    {10.0f, -20.0f,  10.0f }, // 徐々に下降
	    {15.0f, -30.0f,  5.0f  }, // さらに下降
	    {20.0f, -40.0f,  0.0f  }, // 平坦から下降
	    {25.0f, -50.0f,  -5.0f }, // さらに下降
	    {30.0f, -60.0f,  -10.0f}, // 急激な下降
	    {35.0f, -70.0f,  -15.0f}, // さらに下降
	    {40.0f, -75.0f,  -20.0f}, // 最終地点に向かって
	    {45.0f, -80.0f,  -25.0f}, // 最終地点に近づく
	    {50.0f, -85.0f,  -30.0f}, // さらに調整
	    {55.0f, -90.0f,  -35.0f}, // さらに調整
	    {60.0f, -95.0f,  -40.0f}, // さらに調整
	    {50.0f, -100.0f, -45.0f}, // さらに調整
	    {40.0f, -100.0f, -47.5f}, // さらに調整
	    {30.0f, -100.0f, -49.0f}, // さらに調整
	    {20.0f, -100.0f, -49.5f}, // さらに調整
	    {10.0f, -100.0f, -49.8f}, // さらに調整
	    {5.0f,  -100.0f, -49.9f}, // さらに調整
	    {-6.0f, -80.0f,  -50.0f}  // 目的地
	};

	controlPoints_.push_back(controlPoints_.front());

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(viewProjection);
}

// 更新
void RailCamera::Update() {
	// t_ += 1.0f/1000.0f;
	// if (t_ > 1.0f) {
	//	t_ -= 1.0f; // t が 1.0f を超えたらループさせる
	// }
	//  移動
	// worldTransform_.translation_ = Math::CatmullRomPosition(controlPoints_, t_);
	// worldTransform_.rotation_ = Math::CatmullRomPosition(controlPoints_, t_);

#ifdef _DEBUG
	// カメラの座標を画面に表示する処理
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::Text("t%f", t_);
	ImGui::End();

	ImGui::Begin("sprine");
	ImGui::DragFloat3("0", &controlPoints_[0].x, 0.1f);
	ImGui::DragFloat3("1", &controlPoints_[1].x, 0.1f);
	ImGui::DragFloat3("2", &controlPoints_[2].x, 0.1f);
	ImGui::DragFloat3("3", &controlPoints_[3].x, 0.1f);
	ImGui::DragFloat3("4", &controlPoints_[4].x, 0.1f);
	ImGui::End();

#endif // _DEBUG

	// ワールド行列を再計算
	worldTransform_.UpdateMatrix();
	// カメラのオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = ~worldTransform_.matWorld_;
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

// 親子付け
void RailCamera::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
