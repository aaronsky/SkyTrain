#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"

class Entity
{
public:
	Entity(Mesh* _mesh, Transform* _transform, ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);
	~Entity();

	Transform* GetTransform();

	virtual void Update(float deltaTime);

	void Draw(ID3D11DeviceContext* context, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection);
private:
	Mesh* mesh;
	Material* material;
	Transform* transform;
};

