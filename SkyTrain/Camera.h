#pragma once
#include "IGameObject.h"

typedef enum
{
	Left,
	Right,
	Up,
	Down,
	Forward,
	Backward
} CameraDirections;

class Camera : IGameObject
{
public:
	Camera(float aspectRatio);
	~Camera();
	DirectX::XMFLOAT4X4 GetViewMatrix(bool regen = true);
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool regen = false);
	void Move(CameraDirections direction, float dT);
	void Update(float xOffset, float yOffset);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
protected:
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	float aspectRatio;
};

