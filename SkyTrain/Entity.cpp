#include "Entity.h"



Entity::Entity(Mesh * mesh, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale)
{
	this->mesh = mesh;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Entity::~Entity()
{
}

#pragma region Getters
DirectX::XMFLOAT4X4 Entity::GetWorldMatrix()
{
	return this->worldMatrix;
}

DirectX::XMFLOAT4X4 Entity::GetViewMatrix()
{
	return this->viewMatrix;
}

DirectX::XMFLOAT4X4 Entity::GetProjectionMatrix()
{
	return this->projectionMatrix;
}

DirectX::XMFLOAT3 Entity::GetPosition()
{
	return this->position;
}

DirectX::XMFLOAT3 Entity::GetRotation()
{
	return this->rotation;
}

DirectX::XMFLOAT3 Entity::GetScale()
{
	return this->scale;
}
#pragma endregion Getters

#pragma region Setters
void Entity::SetWorldMatrix(DirectX::XMFLOAT4X4 newWorld)
{
	this->worldMatrix = newWorld;
}

void Entity::SetViewMatrix(DirectX::XMFLOAT4X4 newView)
{
	this->viewMatrix = newView;
}

void Entity::SetProjectionMatrix(DirectX::XMFLOAT4X4 newProjection)
{
	this->projectionMatrix = newProjection;
}

void Entity::SetPosition(DirectX::XMFLOAT3 newPosition)
{
	this->position = newPosition;
}

void Entity::SetRotation(DirectX::XMFLOAT3 newRotation)
{
	this->rotation = newRotation;
}

void Entity::SetScale(DirectX::XMFLOAT3 newScale)
{
	this->scale = newScale;
}
#pragma endregion Setters

#pragma region Translate
void Entity::TranslateX(float x)
{
	this->position.x += x;
}

void Entity::TranslateY(float y)
{
	this->position.y += y;
}

void Entity::TranslateZ(float z)
{
	this->position.z += z;
}
#pragma endregion Translate

#pragma region Rotate
void Entity::RotateX(float x)
{
	this->position.x += x;
}

void Entity::RotateY(float y)
{
	this->position.y += y;
}

void Entity::RotateZ(float z)
{
	this->position.z += z;
}
#pragma endregion Rotate

#pragma region Scale
void Entity::ScaleX(float x)
{
	this->position.x += x;
}

void Entity::ScaleY(float y)
{
	this->position.y += y;
}

void Entity::ScaleZ(float z)
{
	this->position.z += z;
}
#pragma endregion Scale

void Entity::Update()
{

}

void Entity::Draw(ID3D11DeviceContext * context)
{
	this->material->SetShader(worldMatrix, viewMatrix, projectionMatrix);

}
