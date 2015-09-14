#pragma once
#include "IGameObject.h"
#include "Mesh.h"
#include "Material.h"
class Entity :
	public IGameObject
{
public:
	Entity(std::shared_ptr<Transform> _transform, Mesh * _mesh, ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);
	~Entity();
	void Draw(ID3D11DeviceContext* context, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection);
private:
	Mesh* mesh;
	Material* material;
};

