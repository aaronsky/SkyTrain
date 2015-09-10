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
	DirectX::XMFLOAT3 GetRotationAxis();
	DirectX::XMFLOAT3 GetScale();

	void SetWorldMatrix(DirectX::XMFLOAT4X4 newWorld);
	void SetPosition(DirectX::XMFLOAT3 newPosition);
	void SetRotationAxis(DirectX::XMFLOAT3 newRotation);
	void SetScale(DirectX::XMFLOAT3 newScale);

	void TranslateX(float x);
	void TranslateY(float y);
	void TranslateZ(float z);

	void Rotate(float degrees, DirectX::XMFLOAT3 axis);
	void RotateX(float degrees, float axisZ);
	void RotateY(float degrees, float axisZ);
	void RotateZ(float degrees, float axisZ);

	void ScaleX(float x);
	void ScaleY(float y);
	void ScaleZ(float z);
protected:
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotationAxis;
	float rotationDegrees;
	DirectX::XMFLOAT3 scale;
	bool isDirty;
};

