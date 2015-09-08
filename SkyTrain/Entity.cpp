#include "Entity.h"

using namespace DirectX;

Entity::Entity(Mesh * _mesh, XMFLOAT3 _position, XMFLOAT3 _rotation, XMFLOAT3 _scale, ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
	this->mesh = _mesh;
	this->material = new Material(_device, _deviceContext, L"VertexShader.cso", L"PixelShader.cso");
	this->position = _position;
	this->rotation = _rotation;
	this->scale = _scale;

	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W));
}

Entity::~Entity()
{
	delete mesh;
	delete material;
}

#pragma region Getters
XMFLOAT4X4 Entity::GetWorldMatrix()
{
	return this->worldMatrix;
}

XMFLOAT3 Entity::GetPosition()
{
	return this->position;
}

XMFLOAT3 Entity::GetRotation()
{
	return this->rotation;
}

XMFLOAT3 Entity::GetScale()
{
	return this->scale;
}
#pragma endregion Getters

#pragma region Setters
void Entity::SetWorldMatrix(XMFLOAT4X4 newWorld)
{
	this->worldMatrix = newWorld;
}

void Entity::SetPosition(XMFLOAT3 newPosition)
{
	this->position = newPosition;
}

void Entity::SetRotation(XMFLOAT3 newRotation)
{
	this->rotation = newRotation;
}

void Entity::SetScale(XMFLOAT3 newScale)
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
	RotateX(0.5f);
}

void Entity::Draw(ID3D11DeviceContext * context, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
	this->material->SetShader(worldMatrix, view, projection);
	this->mesh->Draw(context);
}
