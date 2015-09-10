#pragma once
#include "Vertex.h"
class Transform
{
public:
	Transform(DirectX::XMFLOAT3 _position, DirectX::XMFLOAT3 _rotation, DirectX::XMFLOAT3 _scale);
	~Transform();

	static Transform* Origin();

	DirectX::XMFLOAT4X4 GetWorldMatrix(bool regenIfNeeded = true);
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
protected:
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	bool isDirty;
};

