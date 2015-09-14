#pragma once
#include "Transform.h"
class Camera
{
public:
	Camera(float aspectRatio);
	~Camera();
	DirectX::XMFLOAT4X4 GetViewMatrix(bool regenIfNeeded = true);
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool regen = false);
	void Update(float xOffset, float yOffset);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
protected:
	std::shared_ptr<Transform> transform;
	DirectX::XMVECTOR up;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	float aspectRatio;
	bool isDirty;
};

