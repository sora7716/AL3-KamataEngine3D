#include "Model.h"
#include "WorldTransform.h"

class Player{
public:
	
	
	//初期化
	void Initialize(Model *model,uint32_t textureHandle,ViewProjection* viewprojection);
	//更新
	void Update();
	//描画
	void Draw();


private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	uint32_t textureHandle_ = 0u;

	



};