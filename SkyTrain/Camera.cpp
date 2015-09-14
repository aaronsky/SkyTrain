#include "Camera.h"

using namespace DirectX;

Camera::Camera(float aspectRatio) : IGameObject(std::shared_ptr<Transform>(new Transform(0, 0, -5, 0, 0, 1)))
{
	this->aspectRatio = aspectRatio;
	worldUp = up = XMVectorSet(0, 1, 0, 0);
	UpdateViewMatrix();
	GetProjectionMatrix(true);
}

Camera::~Camera()
{
}

XMFLOAT4X4 Camera::GetViewMatrix(bool regen)
{
	if (regen) {
		UpdateViewMatrix();
	}
	return view;
}

XMFLOAT4X4 Camera::GetProjectionMatrix(bool regen)
{
	if (regen) {
		UpdateProjectionMatrix();
	}
	return projection;
}

void Camera::Update(float xOffset, float yOffset)
{
	float mouseSensitivity = 0.0125f;
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	transform->RotateX(yOffset);
	transform->RotateY(xOffset);
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR posVec = XMLoadFloat3(&(transform->GetPosition()));
	XMVECTOR rotVec = XMLoadFloat3(&(transform->GetRotation()));
	XMVECTOR rotQuaternion = XMQuaternionRotationRollPitchYawFromVector(rotVec);
	XMVECTOR direction = XMVector3Rotate(up, rotQuaternion);
	XMMATRIX V = XMMatrixLookToLH(posVec, direction, up);
	XMStoreFloat4x4(&view, XMMatrixTranspose(V));
}

void Camera::UpdateProjectionMatrix()
{
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.1415926535f, aspectRatio, 0.1f, 100.0f);
	XMStoreFloat4x4(&projection, XMMatrixTranspose(P));
}
