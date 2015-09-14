#include "IGameObject.h"

using namespace DirectX;

IGameObject::IGameObject(std::shared_ptr<Transform> _transform)
{
	this->transform = _transform;
}

IGameObject::~IGameObject()
{
}

std::shared_ptr<Transform> IGameObject::GetTransform()
{
	return transform;
}

void IGameObject::Update(float deltaTime)
{
}

