#pragma once
#include <vector>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
using namespace std;
class Blocks {
private:
	Model* model_ = nullptr;
	uint32_t texture_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	vector<vector<WorldTransform*>> worldTransformBlocks_;


public:
	void Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection);

	void Update();

	void Draw();

	vector<vector<WorldTransform*>> GetBlocks() { return worldTransformBlocks_; };

};
