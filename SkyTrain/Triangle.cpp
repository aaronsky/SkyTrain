#include "Triangle.h"

using namespace DirectX;

Triangle::Triangle(ID3D11Device* device) : Mesh()
{

	Vertex triangleVertices[] =
	{
		{ XMFLOAT3(+0.0f, 0.5f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(+0.5f, -0.5f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
		{ XMFLOAT3(-0.5f, -0.5f, +0.0f), XMFLOAT3(0, 0, -1), XMFLOAT2(0, 0) },
	};

	unsigned int indices[] = { 0, 1, 2 };

	Init(triangleVertices, 3, indices, 3, device);
}


Triangle::~Triangle()
{
}
