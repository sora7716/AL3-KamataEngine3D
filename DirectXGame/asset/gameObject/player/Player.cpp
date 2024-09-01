#include "Player.h"
#include "Model.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "asset/gameObject/player/bullet/PlayerBullet.h"
#include "asset/math/Math.h"
#include "asset/scene/GameScene.h"
#include "input/Input.h"
#include <cassert>
#include "imgui.h"
#include <numbers>

// コンストラクタ
Player::Player() {}

// デストラクタ
Player::~Player() { delete sprite2DReticle_; }

// 初期化
void Player::Initialize(Model* model, ViewProjection* viewProjection,Vector3 position) {
	assert(model);
	model_ = model;                                                                                           // モデル
	viewProjection_ = viewProjection;                                                                         // ビュープロジェクション
	worldTransform_.Initialize();                                                                             // ワールドトランスフォームの初期化
	worldTransform_.translation_ = position;                                                                  // 初期位置
	input_ = Input::GetInstance();                                                                            // シングルインスタンス
	worldTransform3DReticle_.Initialize();                                                                    // 3Dレティクルのワールドトランスフォーム初期化
	//reticleModel_ = Model::Create();                                                                          // レティクルの場所を示すだけのモデルを作成
	uint32_t textureRecticle = TextureManager::Load("kamata.ico");                                            // レティクル用テクスチャ取得
	sprite2DReticle_ = Sprite::Create(textureRecticle, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}); // スプライト生成
}

// 更新
void Player::Update() {
	// デバックテキスト
	DebugText();

	// 攻撃
	Attack();

	//レティクルの更新
	ReticleUpdate();

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += velocity_;

	// マトリックスの更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {
	model_->Draw(worldTransform_, *viewProjection_);       // プレイヤー
	model_->Draw(worldTransform3DReticle_, *viewProjection_);  // レティクルの場所を示すだけのモデル
}

// UIの描画
void Player::DrawUI() { sprite2DReticle_->Draw(); }

// 衝突を検出したら呼び出されるコールバック関数
void Player::OnCollision() {}

// 速度
void Player::SetVelocity(Vector3 velocity) { velocity_ = velocity; }

// ワールドポジションのゲッター
Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

// AABBのゲッター
AABB Player::GetAABB() {
	Vector3 worldPosition = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPosition.x - kWidth / 2.0f, worldPosition.y - kHeight / 2.0f, worldPosition.z - kDepth / 2.0f};
	aabb.max = {worldPosition.x + kWidth / 2.0f, worldPosition.y + kHeight / 2.0f, worldPosition.z + kDepth / 2.0f};
	return aabb;
}

// 親となるワールドトランスフォームをセット
void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
	parentTranslation_ = worldTransform_.parent_->translation_;
}

// ペアレントのトランスレイションのゲッター
Vector3 Player::GetParentTranslation() { return parentTranslation_; }

// ペアレントのローテションのゲッター
Vector3 Player::GetParentRotation() { return parentRotation_; }

// ゲームシーンのセッター
void Player::SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

//レティクルの更新
void Player::ReticleUpdate() {

	// マウスの座標
	POINT mousePosition;
	// マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	// クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	// ビューポートサイズを取得
	float windowWidth = static_cast<float>(WinApp::kWindowWidth);
	float windowHeight = static_cast<float>(WinApp::kWindowHeight);

	// マウス座標を正規化デバイス座標系(NDC)に変換
	float mouseX = (2.0f * mousePosition.x) / windowWidth - 1.0f;
	float mouseY = 1.0f - (2.0f * mousePosition.y) / windowHeight;
	Vector3 posNDC = {mouseX, mouseY, 1.0f}; // 遠平面(z = 1.0f)でのNDC

	// ビュープロジェクション行列の逆行列を取得
	Matrix4x4 matInverseVP = ~(viewProjection_->matView * viewProjection_->matProjection);

	// NDCからワールド座標系への変換（遠平面）
	Vector3 posFar = Math::Transform(posNDC, matInverseVP);

	// NDCを近平面(z = 0)に調整
	posNDC.z = 0.0f;
	Vector3 posNear = Math::Transform(posNDC, matInverseVP);

	// マウスレイの方向を計算
	Vector3 mouseDirection = Math::Normalize(posFar - posNear);

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 50.0f;

	// 3Dレティクルの位置を設定
	worldTransform3DReticle_.translation_ = posNear + mouseDirection * kDistancePlayerTo3DReticle;
	worldTransform3DReticle_.UpdateMatrix();

	// ビューポート行列の作成
	Matrix4x4 matViewport = Math::MakeViewportMatrix(0, 0, windowWidth, windowHeight, 0, 1);

	// ビュー、プロジェクション、ビューポート行列を合成
	Matrix4x4 matViewProjectionViewport = viewProjection_->matView * viewProjection_->matProjection * matViewport;

	// ワールド座標からスクリーン座標へ変換
	Vector3 positionReticle = Math::Transform(worldTransform3DReticle_.translation_, matViewProjectionViewport);

	// スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
}

#ifdef _DEBUG
#include "imgui.h"
void Player::DebugText() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("playerPosition", &worldTransform_.translation_.x);
	ImGui::End();
}
#endif // _DEBUG

// 攻撃
void Player::Attack() {
	Vector3 reticleWorldPos = {
	    worldTransform3DReticle_.matWorld_.m[3][0],
	    worldTransform3DReticle_.matWorld_.m[3][1],
	    worldTransform3DReticle_.matWorld_.m[3][2],
	};
	if (input_->IsTriggerMouse(0)) {
		// 弾の速度
		Vector3 velocity{0, 0, kBulletSpeed};
		velocity = reticleWorldPos - GetWorldPosition();
		velocity = Math::Normalize(velocity) * kBulletSpeed;
		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = Math::TransformNormal(velocity, worldTransform_.matWorld_);
		// 生成
		PlayerBullet* newBullet = new PlayerBullet();
		// 初期化
		newBullet->Initialize(gameScene_->GetPlayerBulletModel(), GetWorldPosition(), velocity);
		// 弾を登録する
		gameScene_->AddPlayerBullet(newBullet);
	}
}

// 左へ移動
void Player::MoveLeft() { velocity_.x -= kCharacterSpeed; }

// 右へ移動
void Player::MoveRight() { velocity_.x += kCharacterSpeed; }

// 下へ移動
void Player::MoveDown() { velocity_.y -= kCharacterSpeed; }

// 上へ移動
void Player::MoveUp() { velocity_.y += kCharacterSpeed; }

// 右回り
void Player::RotateRight() { worldTransform_.rotation_.y -= kRotSpeed; }

// 左回り
void Player::RotateLeft() { worldTransform_.rotation_.y += kRotSpeed; }
