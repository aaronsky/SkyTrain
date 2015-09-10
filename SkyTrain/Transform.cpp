#include "Transform.h"

using namespace DirectX;

Transform::Transform(XMFLOAT3 _position, XMFLOAT3 _rotation, XMFLOAT3 _scale)
{
	this->position = _position;
	this->rotationAxis = _rotation;
	this->rotationDegrees = 0.0f;
	this->scale = _scale;
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W));
	isDirty = false;
}


Transform::~Transform()
{
}

Transform* Transform::Origin()
{
	return new Transform(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
}

#pragma region Getters
XMFLOAT4X4 Transform::GetWorldMatrix(bool regenIfNeeded)
{
	if (regenIfNeeded && isDirty) {
		XMMATRIX trans = XMMatrixTranslation(position.x, position.y, position.z);
		XMVECTOR axis = XMLoadFloat3(&rotationAxis);
		XMMATRIX rot = XMMatrixRotationAxis(axis, rotationDegrees);
		XMMATRIX scale = XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z);
		XMMATRIX w = scale * rot * trans;
		XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(w));
		isDirty = false;
	}
	return this->worldMatrix;
}

XMFLOAT3 Transform::GetPosition()
{
	return this->position;
}

XMFLOAT3 Transform::GetRotationAxis()
{
	return this->rotationAxis;
}

XMFLOAT3 Transform::GetScale()
{
	return this->scale;
}
#pragma endregion Getters

#pragma region Setters
void Transform::SetWorldMatrix(XMFLOAT4X4 newWorld)
{
	this->worldMatrix = newWorld;
	isDirty = true;
}

void Transform::SetPosition(XMFLOAT3 newPosition)
{
	this->position = newPosition;
	isDirty = true;
}

void Transform::SetRotationAxis(XMFLOAT3 newRotation)
{
	this->rotationAxis = newRotation;
	isDirty = true;
}

void Transform::SetScale(XMFLOAT3 newScale)
{
	this->scale = newScale;
	isDirty = true;
}
#pragma endregion Setters

#pragma region Translate
void Transform::TranslateX(float x)
{
	this->position.x += x;
	isDirty = true;
}

void Transform::TranslateY(float y)
{
	this->position.y += y;
	isDirty = true;
}

void Transform::TranslateZ(float z)
{
	this->position.z += z;
	isDirty = true;
}
#pragma endregion Translate

#pragma region Rotate
void Transform::Rotate(float degrees, XMFLOAT3 axis)
{
	SetRotationAxis(axis);
	rotationDegrees += degrees;
	isDirty = true;
}

void Transform::RotateX(float degrees, float axisX)
{
	this->rotationAxis.x = axisX;
	rotationDegrees += degrees;
	isDirty = true;
}

void Transform::RotateY(float degrees, float axisY)
{
	this->rotationAxis.y = axisY;
	rotationDegrees += degrees;
	isDirty = true;
}

void Transform::RotateZ(float degrees, float axisZ)
{
	this->rotationAxis.z = axisZ;
	rotationDegrees += degrees;
	isDirty = true;
}
#pragma endregion Rotate

#pragma region Scale
void Transform::ScaleX(float x)
{
	this->scale.x += x;
	isDirty = true;
}

void Transform::ScaleY(float y)
{
	this->scale.y += y;
	isDirty = true;
}

void Transform::ScaleZ(float z)
{
	this->scale.z += z;
	isDirty = true;
}
#pragma endregion Scale