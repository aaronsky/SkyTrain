#pragma once
#include "Mesh.h"
#include "Material.h"

class Entity
{
public:
	Entity(Mesh* mesh, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale);
	~Entity();
	
	DirectX::XMFLOAT4X4 GetWorldMatrix();
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();

	void SetWorldMatrix(DirectX::XMFLOAT4X4 newWorld);
	void SetViewMatrix(DirectX::XMFLOAT4X4 newView);
	void SetProjectionMatrix(DirectX::XMFLOAT4X4 newProjection);
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

	void Draw(ID3D11DeviceContext* context);
private:
	DirectX::XMFLOAT4X4 worldMatrix;
		DirectX::XMFLOAT4X4 viewMatrix;
		DirectX::XMFLOAT4X4 projectionMatrix;
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
		Mesh* mesh;
		Material* material;
};

