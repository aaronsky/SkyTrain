#include "Pentagon.h"

using namespace DirectX;

Pentagon::Pentagon(ID3D11Device* device) : Mesh()
{
	Vertex pentagonVertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(+0.0f, +0.0f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(-0.951057f, +0.309017f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(-0.587785f, -0.809017f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(+0.587785f, -0.809017f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(+0.951057f, +0.309017f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) }
	};

	unsigned int pentagonIndices[] = { 0, 1, 2, 2, 1, 3, 1, 4, 3, 1, 5, 4, 0, 5, 1 };

	Init(pentagonVertices, 6, pentagonIndices, 15, device);
}


Pentagon::~Pentagon()
{
}
