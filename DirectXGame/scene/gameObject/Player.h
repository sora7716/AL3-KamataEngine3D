#include "Model.h"
#include "WorldTransform.h"

class Player{
public:
	
	
	//初期化
	void Initialize(Model *model,uint32_t texturehundle,ViewProjection* viewprojection);
	//更新
	void Update();
	//描画
	void Draw();


private:
	Model* model_ = nullptr;
	WorldTransform worldtransform_;
	ViewProjection* viewprojection_ = nullptr;
	uint32_t texturehundle_ = 0u;

	



};