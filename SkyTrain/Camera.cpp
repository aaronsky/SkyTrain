#include "Camera.h"

using namespace DirectX;

Camera::Camera(float aspectRatio) : IGameObject(std::shared_ptr<Transform>(new Transform(0, 0, -5, 0, 0, 1)))
{
	this->aspectRatio = aspectRatio;
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

void Camera::Move(CameraDirections direction, float dT)
{
	float velocity = 5.0f * dT;
	switch (direction)
	{
	case Left:
		transform->MoveX(-1.0f * velocity, dT);
		break;
	case Right:
		transform->MoveX(velocity, dT);
		break;
	case Up:
		transform->MoveY(-1.0f * velocity, dT);
		break;
	case Down:
		transform->MoveY(velocity, dT);
		break;
	case Forward:
		transform->MoveY(velocity, dT);
		break;
	case Backward:
		transform->MoveY(-1.0f * velocity, dT);
		break;
	default:
		break;
	}
}

void Camera::Update(float xOffset, float yOffset)
{
	float mouseSensitivity = 0.0125f;
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	transform->RotateX(yOffset);
	transform->RotateY(xOffset);
	transform->UpdateVectors();
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR posVec = XMLoadFloat3(&(transform->GetPosition()));
	XMVECTOR rotVec = XMLoadFloat3(&(transform->GetRotation()));
	XMVECTOR upVec = XMLoadFloat3(&(transform->GetUp()));
	XMVECTOR rotQuaternion = XMQuaternionRotationRollPitchYawFromVector(rotVec);
	XMVECTOR direction = XMVector3Rotate(upVec, rotQuaternion);
	XMMATRIX V = XMMatrixLookToLH(posVec, direction, upVec);
	XMStoreFloat4x4(&view, XMMatrixTranspose(V));
}

void Camera::UpdateProjectionMatrix()
{
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.1415926535f, aspectRatio, 0.1f, 100.0f);
	XMStoreFloat4x4(&projection, XMMatrixTranspose(P));
}
