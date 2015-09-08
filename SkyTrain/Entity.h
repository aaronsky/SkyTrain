#pragma once
#include "Mesh.h"
#include "Material.h"

class Entity
{
public:
	Entity(const Mesh* _mesh, DirectX::XMFLOAT3 _position, DirectX::XMFLOAT3 _rotation, DirectX::XMFLOAT3 _scale, ID3D11Device* _device, ID3D11DeviceContext* _deviceContext);
	~Entity();

	DirectX::XMFLOAT4X4 GetWorldMatrix();
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();

	void SetWorldMatrix(DirectX::XMFLOAT4X4 newWorld);
	void SetPosition(DirectX::XMFLOAT3 newPosition);
	void SetRotation(DirectX::XMFLOAT3 newRotation);
	void SetScale(DirectX::XMFLOAT3 newScale);

	void TranslateX(float x);
	void TranslateY(float y);
	void TranslateZ(float z);

	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);

	void ScaleX(float x);
	void ScaleY(float y);
	void ScaleZ(float z);

	virtual void Update();

	void Draw(ID3D11DeviceContext* context, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection);
private:
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	Mesh* mesh;
	Material* material;
};

