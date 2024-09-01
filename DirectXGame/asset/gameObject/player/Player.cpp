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

// コンストラクタ
Player::Player() {}

// デストラクタ
Player::~Player() { delete sprite2DReticle_; }

// 初期化
void Player::Initialize(Model* model, ViewProjection* viewProjection, uint32_t texture, Vector3 position) {
	assert(model);
	model_ = model;                                                                                           // モデル
	viewProjection_ = viewProjection;                                                                         // ビュープロジェクション
	texture_ = texture;                                                                                       // テクスチャ
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
	model_->Draw(worldTransform_, *viewProjection_, texture_);       // プレイヤー
	//model_->Draw(worldTransform3DReticle_, *viewProjection_);  // レティクルの場所を示すだけのモデル
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

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 50.0f;

	// 自機から3Dレティクルへのオフセット(z方向固定)
	Vector3 offset = {0, 0, kDistancePlayerTo3DReticle};
	// 自機のワールド行列の回転を反映
	Matrix4x4 worldMatrix = Math::MakeAffineMatrix(Math::Normalize(worldTransform_.scale_), worldTransform_.rotation_, worldTransform_.translation_);
	offset = offset * worldMatrix;
	// ベクトルの長さを整える
	offset = Math::Normalize(offset) * kDistancePlayerTo3DReticle;

	// 3Dレティクルの座標を設定
	worldTransform3DReticle_.translation_ = Vector3(offset.x, offset.y, offset.z);
	worldTransform3DReticle_.UpdateMatrix();

	// 3Dレティクルのワールド行列から、ワールド座標を取得
	Vector3 positionReticle = {
	    worldTransform3DReticle_.matWorld_.m[3][0],
	    worldTransform3DReticle_.matWorld_.m[3][1],
	    worldTransform3DReticle_.matWorld_.m[3][2],
	};

	// ビューポート行列
	Matrix4x4 matViewport = Math::MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVP = viewProjection_->matView * viewProjection_->matProjection;
	Matrix4x4 matVPV = matVP * matViewport;

	// 合成行列の逆行列
	Matrix4x4 matInverseVPV = ~matVPV;

	// スクリーン座標
	Vector3 posNear = Vector3((float)mousePosition.x, (float)mousePosition.y, 0);
	Vector3 posFar = Vector3((float)mousePosition.x, (float)mousePosition.y, 1);

	// スクリーン座標系からワールド座標系へ
	posNear = Math::Transform(posNear, matInverseVPV);
	posFar = Math::Transform(posFar, matInverseVPV);

	// マウスレイの方向
	Vector3 mouseDirection = posFar - posNear;
	mouseDirection = Math::Normalize(mouseDirection);

	// 設定距離
	const float kDistanceTestObject = 50.0f;

	// 発射位置を設定
	worldTransform3DReticle_.translation_ = posNear + mouseDirection * kDistanceTestObject;
	worldTransform3DReticle_.translation_.z = offset.z; // Z座標は固定

	// ワールド行列を更新
	worldTransform3DReticle_.UpdateMatrix();

	// ビュー行列とプロジェクション行列、ビューポート行列を合成する
	Matrix4x4 matViewProjectionViewport = viewProjection_->matView * viewProjection_->matProjection * matViewport;

	// ワールド->スクリーン座標変換(ここで3Dから2Dになる)
	positionReticle = Math::Transform(positionReticle, matViewProjectionViewport);

	// スプライトのレティクルに座標設定
	sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));

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
