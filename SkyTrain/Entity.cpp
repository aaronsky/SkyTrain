#include "Entity.h"

using namespace DirectX;

Entity::Entity(Mesh * _mesh, Transform* _transform, ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
	this->mesh = _mesh;
	this->material = new Material(_device, _deviceContext, L"VertexShader.cso", L"PixelShader.cso");
	this->transform = _transform;
}

Entity::~Entity()
{
	delete mesh;
	delete material;
	delete transform;
}

Transform * Entity::GetTransform()
{
	return transform;
}

void Entity::Update(float deltaTime)
{
}

void Entity::Draw(ID3D11DeviceContext * context, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
	XMFLOAT4X4 wm = transform->GetWorldMatrix();
	this->material->SetShader(wm, view, projection);
	this->mesh->Draw(context);
}
