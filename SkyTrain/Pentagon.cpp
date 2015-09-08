#include "Pentagon.h"

using namespace DirectX;

Mesh Pentagon::CreateMesh(ID3D11Device* device)
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex pentagonVertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+0.0f, +0.0f, +0.0f), blue },
		{ XMFLOAT3(-0.951057f, +0.309017f, +0.0f), red },
		{ XMFLOAT3(-0.587785f, -0.809017f, +0.0f), red },
		{ XMFLOAT3(+0.587785f, -0.809017f, +0.0f), red },
		{ XMFLOAT3(+0.951057f, +0.309017f, +0.0f), red }
	};

	unsigned int pentagonIndices[] = { 0, 1, 2, 2, 1, 3, 1, 4, 3, 1, 5, 4, 0, 5, 1 };
	
	return Mesh(pentagonVertices, 6, pentagonIndices, 15, device);
}

Pentagon::Pentagon(ID3D11Device* device) : Mesh(CreateMesh(device))
{
}


Pentagon::~Pentagon()
{
}
