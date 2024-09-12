#pragma once
#include "WorldTransform.h"

class Model;
class ViewProjection;

class SceneText {

public:

	void Initialize(Model* model, ViewProjection *viewProjection);

	void Update();

	void Draw();

	const WorldTransform& GetPosition() const { return worldTransform_; }

	void SetPosition(const Vector3& position);

private:

	Model* model_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	WorldTransform worldTransform_;

};
