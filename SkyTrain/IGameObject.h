#pragma once
#include "Transform.h"

class IGameObject
{
public:
	IGameObject(std::shared_ptr<Transform> _transform);
	~IGameObject();

	std::shared_ptr<Transform> GetTransform();

	virtual void Update(float deltaTime);
protected:
	std::shared_ptr<Transform> transform;
};

