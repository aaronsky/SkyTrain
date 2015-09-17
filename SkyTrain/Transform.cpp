#include "Transform.h"

using namespace DirectX;

Transform::Transform(float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z, float sca_x, float sca_y, float sca_z)
{
	Init(
		XMFLOAT3(pos_x, pos_y, pos_z),
		XMFLOAT3(rot_x, rot_y, rot_z),
		XMFLOAT3(sca_x, sca_y, sca_z)
		);
}

Transform::Transform(XMFLOAT3 _position, XMFLOAT3 _rotation, XMFLOAT3 _scale)
{
	Init(_position, _rotation, _scale);
}

void Transform::Init(XMFLOAT3 _position, XMFLOAT3 _rotation, XMFLOAT3 _scale)
{
	this->position = _position;
	this->rotation = _rotation;
	this->scale = _scale;
	worldUp = XMVectorSet(0, 1, 0, 0);
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W));
	isDirty = false;
}

Transform::~Transform()
{
}

std::shared_ptr<Transform> Transform::Origin()
{
	return std::shared_ptr<Transform>(new Transform(0, 0, 0));
}

void Transform::UpdateVectors()
{
	front.x = cos(XMConvertToRadians(rotation.z)) * cos(XMConvertToRadians(rotation.y));
	front.y = sin(XMConvertToRadians(rotation.y));
	front.z = sin(XMConvertToRadians(rotation.z)) * cos(XMConvertToRadians(rotation.y));
	XMVECTOR frontVec = XMLoadFloat3(&front);
	frontVec = XMVector3Normalize(frontVec);
	XMVECTOR rightVec = XMLoadFloat3(&right);
	XMVECTOR upVec = XMLoadFloat3(&up);
	rightVec = XMVector3Normalize(XMVector3Cross(frontVec, worldUp));
	upVec = XMVector3Normalize(XMVector3Cross(frontVec, rightVec));
	
	XMStoreFloat3(&front, frontVec);
	XMStoreFloat3(&right, rightVec);
	XMStoreFloat3(&up, upVec);
}

#pragma region Getters
XMFLOAT4X4 Transform::GetWorldMatrix(bool regenIfNeeded)
{
	if (regenIfNeeded && isDirty) {
		XMVECTOR posVec = XMLoadFloat3(&position);
		XMVECTOR rotVec = XMLoadFloat3(&rotation);
		XMVECTOR scaleVec = XMLoadFloat3(&scale);

		XMMATRIX w = XMMatrixScalingFromVector(scaleVec) * XMMatrixRotationRollPitchYawFromVector(rotVec) * XMMatrixTranslationFromVector(posVec);

		XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(w));
		isDirty = false;
	}
	return this->worldMatrix;
}

#pragma region Getters - Position
XMFLOAT3 Transform::GetPosition()
{
	return this->position;
}

float Transform::X()
{
	return this->position.x;
}

float Transform::Y()
{
	return this->position.y;
}

float Transform::Z()
{
	return this->position.z;
}
#pragma endregion Getters - Position

XMFLOAT3 Transform::GetRotation()
{
	return this->rotation;
}

XMFLOAT3 Transform::GetScale()
{
	return this->scale;
}

XMFLOAT3 Transform::GetRight()
{
	return this->right;
}

XMFLOAT3 Transform::GetUp()
{
	return this->up;
}

XMFLOAT3 Transform::GetFront()
{
	return this->front;
}
#pragma endregion Getters

#pragma region Setters
void Transform::SetWorldMatrix(XMFLOAT4X4 newWorld)
{
	this->worldMatrix = newWorld;
	isDirty = true;
}

#pragma region Setters - Position
void Transform::SetPosition(XMFLOAT3 newPosition)
{
	this->position = newPosition;
	isDirty = true;
}

void Transform::SetPositionFromVector(DirectX::XMVECTOR newPosition)
{
	XMStoreFloat3(&position, newPosition);
	isDirty = true;
}

void Transform::SetX(float x)
{
	this->position.x = x;
	isDirty = true;
}

void Transform::SetY(float y)
{
	this->position.y = y;
	isDirty = true;
}

void Transform::SetZ(float z)
{
	this->position.z = z;
	isDirty = true;
}


void Transform::MoveX(float x, float dT)
{
	XMVECTOR posVec = XMLoadFloat3(&position);
	XMVECTOR rightVec = XMLoadFloat3(&right);
	if (x > 0)
		posVec = XMVectorAdd(posVec, XMVectorScale(rightVec, x));
	else if (x < 0)
		posVec = XMVectorSubtract(posVec, XMVectorScale(rightVec, x));
	XMStoreFloat3(&position, posVec);
}

void Transform::MoveY(float y, float dT)
{
	XMVECTOR posVec = XMLoadFloat3(&position);
	XMVECTOR upVec = XMLoadFloat3(&up);
	if (y > 0)
		posVec = XMVectorAdd(posVec, XMVectorScale(upVec, y));
	else if (y < 0)
		posVec = XMVectorSubtract(posVec, XMVectorScale(upVec, y));
	XMStoreFloat3(&position, posVec);
}

void Transform::MoveZ(float z, float dT)
{
	XMVECTOR posVec = XMLoadFloat3(&position);
	XMVECTOR frontVec = XMLoadFloat3(&front);
	if (z > 0)
		posVec = XMVectorAdd(posVec, XMVectorScale(frontVec, z));
	else if (z < 0)
		posVec = XMVectorSubtract(posVec, XMVectorScale(frontVec, z));
	XMStoreFloat3(&position, posVec);
}
#pragma endregion Position

void Transform::SetRotation(XMFLOAT3 newRotation)
{
	this->rotation = newRotation;
	isDirty = true;
}

void Transform::SetRotationFromVector(DirectX::XMVECTOR newRotation)
{
	XMStoreFloat3(&rotation, newRotation);
	isDirty = true;
}

void Transform::SetScale(XMFLOAT3 newScale)
{
	this->scale = newScale;
	isDirty = true;
}
void Transform::SetScaleFromVector(DirectX::XMVECTOR newScale)
{
	XMStoreFloat3(&scale, newScale);
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
void Transform::RotateX(float angle)
{
	this->rotation.x += angle;
	isDirty = true;
}

void Transform::RotateY(float angle)
{
	this->rotation.y += angle;
	isDirty = true;
}

void Transform::RotateZ(float angle)
{
	this->rotation.z += angle;
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


void Transform::Update(float dT)
{
}