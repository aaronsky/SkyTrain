#pragma once
#include "Vertex.h"
class Transform
{
public:
	Transform(float pos_x, float pos_y, float pos_z, float rot_x = 0.0f, float rot_y = 0.0f, float rot_z = 0.0f, float sca_x = 1.0f, float sca_y = 1.0f, float sca_z = 1.0f);
	Transform(DirectX::XMFLOAT3 _position, DirectX::XMFLOAT3 _rotation, DirectX::XMFLOAT3 _scale);
	~Transform();

	static Transform* Origin();

	DirectX::XMFLOAT4X4 GetWorldMatrix(bool regenIfNeeded = true);
	DirectX::XMFLOAT3 GetPosition();
	float X();
	float Y();
	float Z();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();

	void SetWorldMatrix(DirectX::XMFLOAT4X4 newWorld);
	void SetPosition(DirectX::XMFLOAT3 newPosition);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetRotation(DirectX::XMFLOAT3 newRotation);
	void SetScale(DirectX::XMFLOAT3 newScale);

	void TranslateX(float x);
	void TranslateY(float y);
	void TranslateZ(float z);

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void ScaleX(float x);
	void ScaleY(float y);
	void ScaleZ(float z);
protected:
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	bool isDirty;
	void Init(DirectX::XMFLOAT3 _position, DirectX::XMFLOAT3 _rotation, DirectX::XMFLOAT3 _scale);
};

