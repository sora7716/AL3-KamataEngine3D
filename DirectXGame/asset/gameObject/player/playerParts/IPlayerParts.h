#pragma once
#include "WorldTransform.h"

class Model;
class ViewProjcection;

class IPlayerParts {

public:

	virtual ~IPlayerParts() = default;

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

private: 

	WorldTransform worldTransform_;

};