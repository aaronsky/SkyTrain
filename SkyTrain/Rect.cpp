#include "Rect.h"

using namespace DirectX;

Rect::Rect(ID3D11Device* device) : Mesh()
{
	Vertex squareVertices[] =
	{
		{ XMFLOAT3(-0.5f, 0.5f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(0.5f, 0.5f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(0.5f, -0.5f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(-0.5f, -0.5f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) }
	};

	unsigned int squareIndices[] = { 0, 1, 2, 0, 2, 3 };

	Init(squareVertices, 4, squareIndices, 6, device);
}


Rect::~Rect()
{
}
