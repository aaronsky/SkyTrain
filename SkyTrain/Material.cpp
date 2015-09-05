#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
	// Delete our simple shaders
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

void Material::SetVertexShader(SimpleVertexShader* newVShader)
{
	this->vertexShader = newVShader;
}

void Material::SetPixelShader(SimplePixelShader* newPShader)
{
	this->pixelShader = newPShader;
}

void Material::SetShader(DirectX::XMFLOAT4X4 world, DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 projection)
{
	this->vertexShader->SetMatrix4x4("world", world);
	this->vertexShader->SetMatrix4x4("view", view);
	this->vertexShader->SetMatrix4x4("projection", projection);

	this->vertexShader->SetShader(true);
	this->pixelShader->SetShader(true);
}