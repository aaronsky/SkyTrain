#include "Material.h"

using namespace DirectX;

Material::Material(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR vertexShaderPath, LPCWSTR pixelShaderPath)
{
	vertexShader = new SimpleVertexShader(device, deviceContext);
	vertexShader->LoadShaderFile(vertexShaderPath);

	pixelShader = new SimplePixelShader(device, deviceContext);
	pixelShader->LoadShaderFile(pixelShaderPath);
}


Material::~Material()
{
	delete vertexShader;
	delete pixelShader;
}

SimpleVertexShader* Material::GetVertexShader()
{
	return this->vertexShader;
}

SimplePixelShader* Material::GetPixelShader()
{
	return this->pixelShader;
}

void Material::SetShader(DirectX::XMFLOAT4X4 world, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
	this->vertexShader->SetMatrix4x4("world", world);
	this->vertexShader->SetMatrix4x4("view", view);
	this->vertexShader->SetMatrix4x4("projection", projection);

	this->vertexShader->SetShader(true);
	this->pixelShader->SetShader(true);
}