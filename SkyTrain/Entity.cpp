#include "Entity.h"

using namespace DirectX;

Entity::Entity(std::shared_ptr<Transform> _transform, 
	Mesh * _mesh, 
	ID3D11Device* _device, 
	ID3D11DeviceContext* _deviceContext)
	: IGameObject(_transform)
{
	this->mesh = _mesh;
	this->material = new Material(_device, _deviceContext, L"VertexShader.cso", L"PixelShader.cso");
}

Entity::~Entity()
{
	delete mesh;
	delete material;
}

void Entity::Draw(ID3D11DeviceContext * context, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
	XMFLOAT4X4 wm = transform->GetWorldMatrix();
	this->material->SetShader(wm, view, projection);
	this->mesh->Draw(context);
}