#include "Material.h"
#include "WICTextureLoader.h"

using namespace DirectX;

Material::Material(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR vertexShaderPath, LPCWSTR pixelShaderPath)
{
	vertexShader = new SimpleVertexShader(device, deviceContext);
	vertexShader->LoadShaderFile(vertexShaderPath);

	pixelShader = new SimplePixelShader(device, deviceContext);
	pixelShader->LoadShaderFile(pixelShaderPath);

	DirectX::CreateWICTextureFromFile(device, deviceContext, L"stone_normal.png", 0, &diffuse);
	DirectX::CreateWICTextureFromFile(device, deviceContext, L"stone_specular.png", 0, &specularMap);

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	device->CreateSamplerState(&samplerDesc, &samplerState);
}


Material::~Material()
{
	delete vertexShader;
	delete pixelShader;

	ReleaseMacro(diffuse);
	ReleaseMacro(specularMap);
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

	this->pixelShader->SetShaderResourceView("diffuseTexture", diffuse);
	this->pixelShader->SetShaderResourceView("specMapTexture", specularMap);
	this->pixelShader->SetSamplerState("trilinear", samplerState);

	this->vertexShader->SetShader(true);
	this->pixelShader->SetShader(true);
}