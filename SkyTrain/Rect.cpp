#include "Rect.h"

using namespace DirectX;

Mesh Rect::CreateMesh(ID3D11Device* device)
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex squareVertices[] =
	{
		{ XMFLOAT3(-0.5f, 0.5f, +0.0f), green },
		{ XMFLOAT3(0.5f, 0.5f, +0.0f), blue },
		{ XMFLOAT3(0.5f, -0.5f, +0.0f), green },
		{ XMFLOAT3(-0.5f, -0.5f, +0.0f), blue }
	};

	unsigned int squareIndices[] = { 0, 1, 2, 0, 2, 3 };

	return Mesh(squareVertices, 4, squareIndices, 6, device);
}

Rect::Rect(ID3D11Device* device) : Mesh(CreateMesh(device))
{
}


Rect::~Rect()
{
}
