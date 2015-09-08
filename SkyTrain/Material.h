#pragma once
#include "SimpleShader.h"

class Material
{
public:
	Material(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR vertexShaderPath, LPCWSTR pixelShaderPath);
	~Material();
	SimpleVertexShader* GetVertexShader();
	SimplePixelShader* GetPixelShader();
	void SetShader(DirectX::XMFLOAT4X4 world, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection);
private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};