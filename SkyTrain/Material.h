#pragma once
#include "SimpleShader.h"

class Material
{
public:
	Material();
	~Material();
	SimpleVertexShader* GetVertexShader();
	SimplePixelShader* GetPixelShader();
	void SetVertexShader(SimpleVertexShader* newVShader);
	void SetPixelShader(SimplePixelShader* newPShader);
	void SetShader(DirectX::XMFLOAT4X4 world, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection);
private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};