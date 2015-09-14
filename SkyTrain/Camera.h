#pragma once
#include "IGameObject.h"
class Camera : IGameObject
{
public:
	Camera(float aspectRatio);
	~Camera();
	DirectX::XMFLOAT4X4 GetViewMatrix(bool regen = true);
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool regen = false);
	void Update(float xOffset, float yOffset);
	void UpdateVectors();
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
protected:
	DirectX::XMVECTOR up;
	DirectX::XMVECTOR worldUp;
	DirectX::XMVECTOR right;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	float aspectRatio;
};

