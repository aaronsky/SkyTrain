#pragma once
#include <memory>
#include "Vertex.h"
#include "IComponent.h"

class Transform : IComponent
{
public:
	Transform(float pos_x, float pos_y, float pos_z, float rot_x = 0.0f, float rot_y = 0.0f, float rot_z = 0.0f, float sca_x = 1.0f, float sca_y = 1.0f, float sca_z = 1.0f);
	Transform(DirectX::XMFLOAT3 _position, DirectX::XMFLOAT3 _rotation, DirectX::XMFLOAT3 _scale);
	~Transform();

	static std::shared_ptr<Transform> Origin();

#pragma region Getters
	DirectX::XMFLOAT4X4 GetWorldMatrix(bool regenIfNeeded = true);
#pragma region Getters - Position
	DirectX::XMFLOAT3 GetPosition();
	float X();
	float Y();
	float Z();
#pragma endregion Getters - Position
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();

	DirectX::XMFLOAT3 GetRight();
	DirectX::XMFLOAT3 GetUp();
	DirectX::XMFLOAT3 GetFront();
#pragma endregion Getters

#pragma region Setters
	void SetWorldMatrix(DirectX::XMFLOAT4X4 newWorld);
#pragma region Setters - Position
	void SetPosition(DirectX::XMFLOAT3 newPosition);
	void SetPositionFromVector(DirectX::XMVECTOR newPosition);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
#pragma endregion Position
	void SetRotation(DirectX::XMFLOAT3 newRotation);
	void SetRotationFromVector(DirectX::XMVECTOR newRotation);
	void SetScale(DirectX::XMFLOAT3 newScale);
	void SetScaleFromVector(DirectX::XMVECTOR newScale);
#pragma endregion Setters

#pragma region Translate
	void TranslateX(float x);
	void TranslateY(float y);
	void TranslateZ(float z);

	void MoveX(float x, float dT);
	void MoveY(float y, float dT);
	void MoveZ(float z, float dT);
#pragma endregion Translate

#pragma region Rotate
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
#pragma endregion Rotate

#pragma region Scale
	void ScaleX(float x);
	void ScaleY(float y);
	void ScaleZ(float z);
#pragma endregion Scale

	void Update(float dT);
	void UpdateVectors();
protected:
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	DirectX::XMFLOAT3 right;
	DirectX::XMFLOAT3 up;
	DirectX::XMFLOAT3 front;
	DirectX::XMVECTOR worldUp;

	bool isDirty;
	void Init(DirectX::XMFLOAT3 _position, DirectX::XMFLOAT3 _rotation, DirectX::XMFLOAT3 _scale);
};

