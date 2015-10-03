#include "Camera.h"
#include <Windows.h>

using namespace DirectX;

// Creates a camera at the specified position
Camera::Camera(float x, float y, float z) : IGameObject(std::shared_ptr<Transform>(new Transform(x, y, z)))
{
	startPosition = XMFLOAT3(x, y, z);
	this->GetTransform()->SetPosition(startPosition);
	XMStoreFloat4(&rotation, XMQuaternionIdentity());
	xRotation = 0;
	yRotation = 0;

	XMStoreFloat4x4(&viewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&projMatrix, XMMatrixIdentity());
}

// Nothing to really do
Camera::~Camera()
{ }


// Moves the camera relative to its orientation
void Camera::MoveRelative(float x, float y, float z)
{
	// Rotate the desired movement vector
	XMVECTOR dir = XMVector3Rotate(XMVectorSet(x, y, z, 0), XMLoadFloat4(&rotation));

	// Move in that direction
	XMStoreFloat3(&(this->GetTransform()->GetPosition()), XMLoadFloat3(&(this->GetTransform()->GetPosition())) + dir);
}

// Moves the camera in world space (not local space)
void Camera::MoveAbsolute(float x, float y, float z)
{
	// Simple add, no need to load/store
	this->GetTransform()->TranslateX(x);
	this->GetTransform()->TranslateY(y);
	this->GetTransform()->TranslateZ(z);
}

// Rotate on the X and/or Y axis
void Camera::Rotate(float x, float y)
{
	// Adjust the current rotation
	xRotation += x;
	yRotation += y;

	// Clamp the x between PI/2 and -PI/2
	xRotation = max(min(xRotation, XM_PIDIV2), -XM_PIDIV2);

	// Recreate the quaternion
	XMStoreFloat4(&rotation, XMQuaternionRotationRollPitchYaw(xRotation, yRotation, 0));
}

// Camera's update, which looks for key presses
void Camera::Update(float dt)
{
	// Current speed
	float speed = dt * 3;

	// Speed up when shift is pressed
	if (GetAsyncKeyState(VK_SHIFT)) { speed *= 5; }

	// Movement
	if (GetAsyncKeyState('W') & 0x8000) { MoveRelative(0, 0, speed); }
	if (GetAsyncKeyState('S') & 0x8000) { MoveRelative(0, 0, -speed); }
	if (GetAsyncKeyState('A') & 0x8000) { MoveRelative(-speed, 0, 0); }
	if (GetAsyncKeyState('D') & 0x8000) { MoveRelative(speed, 0, 0); }
	if (GetAsyncKeyState('X') & 0x8000) { MoveAbsolute(0, -speed, 0); }
	if (GetAsyncKeyState(' ') & 0x8000) { MoveAbsolute(0, speed, 0); }

	// Check for reset
	if (GetAsyncKeyState('R') & 0x8000)
	{
		this->GetTransform()->SetPosition(startPosition);
		xRotation = 0;
		xRotation = 0;
		XMStoreFloat4(&rotation, XMQuaternionIdentity());
	}

	// Update the view every frame - could be optimized
	UpdateViewMatrix();
}

// Creates a new view matrix based on current position and orientation
void Camera::UpdateViewMatrix()
{
	// Rotate the standard "forward" matrix by our rotation
	// This gives us our "look direction"
	XMVECTOR dir = XMVector3Rotate(XMVectorSet(0, 0, 1, 0), XMLoadFloat4(&rotation));

	XMMATRIX view = XMMatrixLookToLH(
		XMLoadFloat3(&(this->GetTransform()->GetPosition())),
		dir,
		XMVectorSet(0, 1, 0, 0));

	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(view));
}

// Updates the projection matrix
void Camera::UpdateProjectionMatrix(float aspectRatio)
{
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		aspectRatio,				// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}