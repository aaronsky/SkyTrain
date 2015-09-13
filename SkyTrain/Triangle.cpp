#include "Triangle.h"

using namespace DirectX;

Mesh Triangle::CreateMesh(ID3D11Device* device)
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex triangleVertices[] =
	{
		{ XMFLOAT3(+0.0f, 0.5f, +0.0f), red },
		{ XMFLOAT3(+0.5f, -0.5f, +0.0f), blue },
		{ XMFLOAT3(-0.5f, -0.5f, +0.0f), green },
	};

	unsigned int indices[] = { 0, 1, 2 };

	return Mesh(triangleVertices, 3, indices, 3, device);
}

Triangle::Triangle(ID3D11Device* device) : Mesh(CreateMesh(device))
{
	
}


Triangle::~Triangle()
{
}
